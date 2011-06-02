/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006 Andrew Hawkins

   This file is part of flactag.

   Flactag is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#include "MusicBrainzInfo.h"

#include <sstream>

#include "base64.h"

#include "DiscIDWrapper.h"
#include "ErrorLog.h"

#include "MusicBrainz/HTTPFetch.h"
#include "MusicBrainz/MusicBrainz-adh.h"
#include "MusicBrainz/Track.h"
#include "MusicBrainz/Release.h"
#include "MusicBrainz/Medium.h"
#include "MusicBrainz/ReleaseGroup.h"
#include "MusicBrainz/ArtistCredit.h"
#include "MusicBrainz/Artist.h"
#include "MusicBrainz/Recording.h"

CMusicBrainzInfo::CMusicBrainzInfo(const std::string& Server, const CCuesheet& Cuesheet)
:	m_Server(Server),
	m_Cuesheet(Cuesheet)
{
	if (m_Server.empty())
		m_Server="musicbrainz.org";
}

bool CMusicBrainzInfo::LoadInfo(const std::string& FlacFile)
{
	bool RetVal=false;

	CDiscIDWrapper DiscIDWrapper;
	DiscIDWrapper.FromCuesheet(m_Cuesheet);
	std::string DiskID=DiscIDWrapper.ID();

	//Test Disk ID for album title containing extended characters
	//DiskID="5EgKduVn7sQH9JGg8JQyrPOjSqc-";

	//CErrorLog::Log("DiskID: " + DiskID);
	//CErrorLog::Log("Submit: " + DiscIDWrapper.SubmitURL());

	MusicBrainzADH::CMusicBrainzADH MusicBrainz;
			
	WaitRequest();

	MusicBrainzADH::CGenericList<MusicBrainzADH::CRelease> ReleaseList=MusicBrainz.LookupDiscID(DiskID);
	std::vector<MusicBrainzADH::CRelease> Releases=ReleaseList.Items();
		
	if (Releases.size())
	{
		RetVal=true;

		std::vector<MusicBrainzADH::CRelease>::const_iterator ThisRelease=Releases.begin();
		while (ThisRelease!=Releases.end())
		{
			MusicBrainzADH::CRelease Release=*ThisRelease;
			
			WaitRequest();
			MusicBrainzADH::CRelease FullRelease=MusicBrainz.LookupRelease(Release.ID());

			std::vector<MusicBrainzADH::CMedium> Media=FullRelease.MediaMatchingDiscID(DiskID);
			std::vector<MusicBrainzADH::CMedium>::const_iterator ThisMedium=Media.begin();
			while (ThisMedium!=Media.end())
			{
				MusicBrainzADH::CMedium Medium=*ThisMedium;
							
				CAlbum Album;
	
				if (FullRelease.ReleaseGroup() || !FullRelease.ReleaseGroup()->Title().empty())
					Album.SetName(FullRelease.ReleaseGroup()->Title());
				else
					Album.SetName(FullRelease.Title());
				
				if (FullRelease.MediumList() && FullRelease.MediumList()->Items().size()>1)
					Album.SetDiskNumber(Medium.Position());
		
				Album.SetAlbumID(FullRelease.ID());
	
				std::string ArtistName;
				std::string ArtistSort;
					
				bool FirstArtist=true;
				MusicBrainzADH::CArtistCredit *ArtistCredit=FullRelease.ArtistCredit();
				if (ArtistCredit)
				{
					std::vector<MusicBrainzADH::CNameCredit> NameCredits=ArtistCredit->NameCredits();
					std::vector<MusicBrainzADH::CNameCredit>::const_iterator ThisNameCredit=NameCredits.begin();
					while (ThisNameCredit!=NameCredits.end())
					{
						MusicBrainzADH::CNameCredit NameCredit=*ThisNameCredit;
						MusicBrainzADH::CArtist *Artist=NameCredit.Artist();
						
						if (!NameCredit.Name().empty())
							ArtistName+=NameCredit.Name();
						else if (Artist)
							ArtistName+=Artist->Name();
							
						ArtistName+=NameCredit.JoinPhrase();
						
						if (Artist)
						{
							ArtistSort+=Artist->SortName();
							ArtistSort+=NameCredit.JoinPhrase();
						}
							
						
						if (FirstArtist)
						{
							FirstArtist=false;
							if (Artist)
								Album.SetArtistID(Artist->ID());
						}
						
						++ThisNameCredit;
					}

					Album.SetArtist(ArtistName);
					Album.SetArtistSort(ArtistSort);
				}
	
				Album.SetASIN(FullRelease.ASIN());
	
				if (!Album.ASIN().empty())
				{
					std::string URL="/images/P/" + Album.ASIN().DisplayValue() + ".02.LZZZZZZZ.jpg";
	
					CHTTPFetch Fetch("images.amazon.com");
	
					int Bytes=Fetch.Fetch(URL);
					if (Bytes<1000)
					{
						URL="/images/P/" + Album.ASIN().DisplayValue() + ".02.MZZZZZZZ.jpg";
						Bytes=Fetch.Fetch(URL);
					}
	
					if (Bytes>0)
					{
						if (Bytes<1000)
							CErrorLog::Log("Album art downloaded was less than 1000 bytes, ignoring");
						else
						{
							std::vector<unsigned char> Data=Fetch.Data();
							Album.SetCoverArt(CCoverArt(&Data[0],Data.size()));
						}
					}
					else
						CErrorLog::Log(std::string("Error downloading art: ") + Fetch.ErrorMessage());
				}

				if (FullRelease.ReleaseGroup())	
						Album.SetType(AlbumType(FullRelease.ReleaseGroup()->Type()));
						
				Album.SetStatus(AlbumStatus(FullRelease.Status()));

/*
				std::vector<std::string> Types=Release->getTypes();
				std::vector<std::string>::const_iterator ThisType=Types.begin();
				while (ThisType!=Types.end())
				{
					std::string ThisName=(*ThisType);
	
					if (ThisName==MusicBrainz::Release::TYPE_OFFICIAL || ThisName==MusicBrainz::Release::TYPE_PROMOTION || ThisName==MusicBrainz::Release::TYPE_BOOTLEG)
						Album.SetStatus(AlbumStatus(MusicBrainz::extractFragment(ThisName)));
					else
						Album.SetType(AlbumType(MusicBrainz::extractFragment(ThisName)));
	
					++ThisType;
				}
*/	
				MusicBrainzADH::CGenericList<MusicBrainzADH::CTrack> *TrackList=Medium.TrackList();
				if (TrackList)
				{
					std::vector<MusicBrainzADH::CTrack> Tracks=TrackList->Items();
					std::vector<MusicBrainzADH::CTrack>::const_iterator ThisTrack=Tracks.begin();
					while (ThisTrack!=Tracks.end())
					{
						MusicBrainzADH::CTrack MBTrack=*ThisTrack;
							
						CTrack Track;
	
						Track.SetNumber(MBTrack.Position());
						
						if (!MBTrack.Title().empty())
							Track.SetName(MBTrack.Title());
						else if (MBTrack.Recording())
							Track.SetName(MBTrack.Recording()->Title());
	
						std::string ArtistName;
						std::string ArtistSort;
							
						bool FirstArtist=true;
						if (MBTrack.Recording())
						{
							MusicBrainzADH::CArtistCredit *ArtistCredit=MBTrack.Recording()->ArtistCredit();
							if (ArtistCredit)
							{
								std::vector<MusicBrainzADH::CNameCredit> NameCredits=ArtistCredit->NameCredits();
								std::vector<MusicBrainzADH::CNameCredit>::const_iterator ThisNameCredit=NameCredits.begin();
								while (ThisNameCredit!=NameCredits.end())
								{
									MusicBrainzADH::CNameCredit NameCredit=*ThisNameCredit;
									MusicBrainzADH::CArtist *Artist=NameCredit.Artist();
									
									if (!NameCredit.Name().empty())
										ArtistName+=NameCredit.Name();
									else if (Artist)
										ArtistName+=Artist->Name();
										
									ArtistName+=NameCredit.JoinPhrase();
									
									if (Artist)
									{
										ArtistSort+=Artist->SortName();
										ArtistSort+=NameCredit.JoinPhrase();
									}
									
									if (FirstArtist)
									{
										FirstArtist=false;
										if (Artist)
											Track.SetArtistID(Artist->ID());
									}
									
									++ThisNameCredit;
								}
							}
						}
							
						Track.SetArtist(ArtistName);
						Track.SetArtistSort(ArtistSort);
		
						if (MBTrack.Recording())
							Track.SetTrackID(MBTrack.Recording()->ID());
		
						Album.AddTrack(Track);
						
						++ThisTrack;
					}
				}
		
				std::string AlbumDate=FullRelease.Date();

				std::string::size_type MinusPos=AlbumDate.find("-");
				if (std::string::npos!=MinusPos)
					AlbumDate=AlbumDate.substr(0,MinusPos);

				Album.SetDate(AlbumDate);
	
				m_Albums.push_back(Album);
				
				++ThisMedium;
			}

			++ThisRelease;
		}
	}
	else
	{
		std::stringstream os;
		os << "No albums found for file '" << FlacFile << "'";
		CErrorLog::Log(os.str());

		CErrorLog::Log("Please submit the DiskID using the following URL:");
		CErrorLog::Log(DiscIDWrapper.SubmitURL());
	}

	return RetVal;
}

std::vector<CAlbum> CMusicBrainzInfo::Albums() const
{
	return m_Albums;
}

std::string CMusicBrainzInfo::AlbumType(const std::string Type) const
{
	const char *AlbumTypeStrings[] =
	{
		"album", "single", "EP", "compilation", "soundtrack",
		"spokenword", "interview", "audiobook", "live", "remix", "other", "\0"
	};

	std::string Ret;

	int i=0;

	while (AlbumTypeStrings[i][0]!='\0')
	{
		if (strcasecmp(Type.c_str(),AlbumTypeStrings[i])==0)
		{
			Ret=AlbumTypeStrings[i];
			break;
		}

		++i;
	}

	return Ret;
}

std::string CMusicBrainzInfo::AlbumStatus(const std::string Status) const
{
	const char *AlbumStatusStrings[] =
	{
		"official", "promotion", "bootleg", "\0"
	};

	std::string Ret;

	int i=0;

	while (AlbumStatusStrings[i][0]!='\0')
	{
		if (strcasecmp(Status.c_str(),AlbumStatusStrings[i])==0)
		{
			Ret=AlbumStatusStrings[i];
			break;
		}

		++i;
	}

	return Ret;
}

void CMusicBrainzInfo::WaitRequest() const
{
	if (m_Server.find("musicbrainz.org")!=std::string::npos)
	{
		static time_t LastRequest=0;
		const time_t TimeBetweenRequests=2;
	
		time_t TimeNow;
	
		do
		{
			TimeNow=time(NULL);
			if (abs(TimeNow-LastRequest)<TimeBetweenRequests)
				usleep(100000);
		}	while (abs(TimeNow-LastRequest)<TimeBetweenRequests);
		
		LastRequest=TimeNow;
	}
}

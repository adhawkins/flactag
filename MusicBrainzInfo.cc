/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006-2012 Andrew Hawkins
   Copyright (C) 2011-2012 Daniel Pocock

   This file is part of flactag.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
	 the Free Software Foundation, either version 3 of the License, or
	 (at your option) any later version.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#include "MusicBrainzInfo.h"

#include "config.h"

#include <sstream>

#include "base64.h"

#include "DiscIDWrapper.h"
#include "ErrorLog.h"

#include "musicbrainz4/HTTPFetch.h"
#include "musicbrainz4/Query.h"
#include "musicbrainz4/Track.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/Medium.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/Artist.h"
#include "musicbrainz4/Recording.h"
#include "musicbrainz4/NameCredit.h"

CMusicBrainzInfo::CMusicBrainzInfo(const std::string& Server, int Port, const CCuesheet& Cuesheet)
:	m_Server(Server),
	m_Port(Port),
	m_Cuesheet(Cuesheet),
	m_DiscIDWrapper(),
	m_DiskID(""),
	m_OverrideDiskID(false)
{
	if (m_Server.empty())
		m_Server="musicbrainz.org";

	if (0==m_Port)
		m_Port=80;

	m_DiscIDWrapper.FromCuesheet(m_Cuesheet);
	m_DiskID.assign(m_DiscIDWrapper.ID());
}

CMusicBrainzInfo::CMusicBrainzInfo(const std::string& Server, int Port, const CCuesheet& Cuesheet, std::string DiskID)
:       m_Server(Server),
        m_Port(Port),
        m_Cuesheet(Cuesheet),
        m_DiscIDWrapper(),
	m_DiskID(DiskID),
	m_OverrideDiskID(true)
{
        if (m_Server.empty())
                m_Server="musicbrainz.org";

        if (0==m_Port)
                m_Port=80;

        m_DiscIDWrapper.FromCuesheet(m_Cuesheet);
}

bool CMusicBrainzInfo::LoadInfo(const std::string& FlacFile)
{
	//http://www.musicbrainz.org/ws/2/discid/arIS30RPWowvwNEqsqdDnZzDGhk-?inc=recordings+artists+artist-credits+url-rels+aliases

	bool RetVal=false;

	//std::string DiskID=DiscIDWrapper.ID();

	//Test Disk ID for album title containing extended characters
	//DiskID="5EgKduVn7sQH9JGg8JQyrPOjSqc-";

	//CErrorLog::Log("DiskID: " + DiskID);
	//CErrorLog::Log("Submit: " + DiscIDWrapper.SubmitURL());

	MusicBrainz4::CQuery MusicBrainz("flactag-" VERSION,m_Server,m_Port);

	try
	{
		MusicBrainz4::CReleaseList ReleaseList=MusicBrainz.LookupDiscID(m_DiskID);

		if (ReleaseList.NumItems())
		{
			RetVal=true;

			for (int ReleaseNum=0;ReleaseNum<ReleaseList.NumItems();ReleaseNum++)
			{
				MusicBrainz4::CRelease *Release=ReleaseList.Item(ReleaseNum);

				MusicBrainz4::CRelease FullRelease=MusicBrainz.LookupRelease(Release->ID());

				MusicBrainz4::CMediumList MediaList=FullRelease.MediaMatchingDiscID(m_DiskID);
	 			for (int MediumNumber=0;MediumNumber<MediaList.NumItems();MediumNumber++)
				{
					MusicBrainz4::CMedium *Medium=MediaList.Item(MediumNumber);

					CAlbum Album=ParseAlbum(FullRelease,Medium);

					MusicBrainz4::CTrackList *TrackList=Medium->TrackList();
					if (TrackList)
					{
						for (int TrackNumber=0;TrackNumber<TrackList->NumItems();TrackNumber++)
						{
							MusicBrainz4::CTrack *MBTrack=TrackList->Item(TrackNumber);

							CTrack Track=ParseTrack(MBTrack);

							Album.AddTrack(Track);
						}
					}

					m_Albums.push_back(Album);
				}
			}
		}
		else
		{
			std::stringstream os;
			os << "No albums found for file '" << FlacFile << "'";
			CErrorLog::Log(os.str());

			if(!m_OverrideDiskID)
			{
				CErrorLog::Log("Please submit the DiskID using the following URL:");
				CErrorLog::Log(m_DiscIDWrapper.SubmitURL());
			}
		}
	}

	catch (MusicBrainz4::CResourceNotFoundError Exception)
	{
			std::stringstream os;
			os << "No albums found for file '" << FlacFile << "'";
			CErrorLog::Log(os.str());

			CErrorLog::Log("Please submit the DiskID using the following URL:");
			CErrorLog::Log(m_DiscIDWrapper.SubmitURL());
	}

	catch (MusicBrainz4::CExceptionBase Exception)
	{
		std::cerr << FlacFile << ": Exception: " << Exception.what() << std::endl;
	}

	return RetVal;
}

std::vector<unsigned char> CMusicBrainzInfo::GetCoverArt(const CUTF8Tag& ASIN)
{
	std::vector<unsigned char> Data;

	std::string URL="/images/P/" + ASIN.DisplayValue() + ".02.LZZZZZZZ.jpg";

	MusicBrainz4::CHTTPFetch Fetch("flactag/v" VERSION, "images.amazon.com");

	int Bytes=Fetch.Fetch(URL);
	if (Bytes<1000)
	{
		URL="/images/P/" + ASIN.DisplayValue() + ".02.MZZZZZZZ.jpg";
		Bytes=Fetch.Fetch(URL);
	}

	if (Bytes>0)
	{
		if (Bytes<1000)
			CErrorLog::Log("Album art downloaded was less than 1000 bytes, ignoring");
		else
		{
			Data=Fetch.Data();
		}
	}
	else
		CErrorLog::Log(std::string("Error downloading art: ") + Fetch.ErrorMessage());

	return Data;
}

CAlbum CMusicBrainzInfo::ParseAlbum(const MusicBrainz4::CRelease& Release, const MusicBrainz4::CMedium* Medium)
{
	CAlbum Album;

	if (!Release.Title().empty())
		Album.SetName(Release.Title());
	else if (Release.ReleaseGroup() && !Release.ReleaseGroup()->Title().empty())
		Album.SetName(Release.ReleaseGroup()->Title());

	if (Release.MediumList() && Release.MediumList()->NumItems()>1)
		Album.SetDiskNumber(Medium->Position());

	Album.SetAlbumID(Release.ID());

	MusicBrainz4::CArtistCredit *ArtistCredit=Release.ArtistCredit();
	if (ArtistCredit)
	{
		std::string ArtistID;
		std::string ArtistName;
		std::string ArtistSort;

		ParseArtist(ArtistCredit,ArtistID,ArtistName,ArtistSort);

		Album.SetArtistID(ArtistID);
		Album.SetArtist(ArtistName);
		Album.SetArtistSort(ArtistSort);
	}

	Album.SetASIN(Release.ASIN());

	if (!Album.ASIN().empty())
	{
		std::vector<unsigned char> Data=GetCoverArt(Album.ASIN());
		if (Data.size()>1000)
			Album.SetCoverArt(CCoverArt(&Data[0],Data.size()));
	}

	if (Release.ReleaseGroup())
			Album.SetType(AlbumType(Release.ReleaseGroup()->Type()));

	Album.SetStatus(AlbumStatus(Release.Status()));

	std::string AlbumDate=Release.Date();

	std::string::size_type MinusPos=AlbumDate.find("-");
	if (std::string::npos!=MinusPos)
		AlbumDate=AlbumDate.substr(0,MinusPos);

	Album.SetDate(AlbumDate);

	return Album;
}

void CMusicBrainzInfo::ParseArtist(const MusicBrainz4::CArtistCredit* ArtistCredit, std::string& ArtistID, std::string& ArtistName, std::string& ArtistSort)
{
	bool FirstArtist=true;

	MusicBrainz4::CNameCreditList *NameCreditsList=ArtistCredit->NameCreditList();
	if (NameCreditsList)
	{
		for (int NameCreditNumber=0;NameCreditNumber<NameCreditsList->NumItems();NameCreditNumber++)
		{
			MusicBrainz4::CNameCredit *NameCredit=NameCreditsList->Item(NameCreditNumber);

			MusicBrainz4::CArtist *Artist=NameCredit->Artist();

			if (!NameCredit->Name().empty())
				ArtistName+=NameCredit->Name();
			else if (Artist)
				ArtistName+=Artist->Name();

			ArtistName+=NameCredit->JoinPhrase();

			if (Artist)
			{
				ArtistSort+=Artist->SortName();
				ArtistSort+=NameCredit->JoinPhrase();
			}

			if (FirstArtist)
			{
				FirstArtist=false;
				if (Artist)
					ArtistID=Artist->ID();
			}
		}
	}
}

CTrack CMusicBrainzInfo::ParseTrack(const MusicBrainz4::CTrack* MBTrack)
{
	CTrack Track;

	Track.SetNumber(MBTrack->Position());

	if (!MBTrack->Title().empty())
		Track.SetName(MBTrack->Title());
	else if (MBTrack->Recording())
		Track.SetName(MBTrack->Recording()->Title());

	if (MBTrack->Recording())
	{
		MusicBrainz4::CArtistCredit *ArtistCredit=MBTrack->Recording()->ArtistCredit();
		if (ArtistCredit)
		{
			std::string ArtistID;
			std::string ArtistName;
			std::string ArtistSort;

			ParseArtist(ArtistCredit,ArtistID,ArtistName,ArtistSort);

			Track.SetArtistID(ArtistID);
			Track.SetArtist(ArtistName);
			Track.SetArtistSort(ArtistSort);
		}

		Track.SetTrackID(MBTrack->Recording()->ID());
	}

	return Track;
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


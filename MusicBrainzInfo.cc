/* --------------------------------------------------------------------------

	 flactag -- A tagger for single album FLAC files with embedded CUE sheets
							using data retrieved from the MusicBrainz service

	 Copyright (C) 2006-2022 Andrew Hawkins
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

#include "CoverArtFetch.h"
#include "DiscIDWrapper.h"
#include "ErrorLog.h"

#include "musicbrainz5/HTTPFetch.h"
#include "musicbrainz5/Query.h"
#include "musicbrainz5/Track.h"
#include "musicbrainz5/Release.h"
#include "musicbrainz5/Medium.h"
#include "musicbrainz5/ReleaseGroup.h"
#include "musicbrainz5/ArtistCredit.h"
#include "musicbrainz5/Artist.h"
#include "musicbrainz5/Recording.h"
#include "musicbrainz5/NameCredit.h"

CMusicBrainzInfo::CMusicBrainzInfo(const CConfigFile &ConfigFile, const CCuesheet &Cuesheet, bool OverrideDiskID, const std::string &DiskID)
		: m_ConfigFile(ConfigFile),
			m_Cuesheet(Cuesheet),
			m_DiscIDWrapper(),
			m_DiskID(DiskID),
			m_OverrideDiskID(OverrideDiskID)
{
	m_Server = m_ConfigFile.Value(CConfigFile::tConfigEntry::Server);

	if (m_Server.empty())
		m_Server="musicbrainz.org";

	int Port = 80;
	std::stringstream os;
	os << m_ConfigFile.Value(CConfigFile::tConfigEntry::Port);
	os >> m_Port;

	if (0==m_Port)
		m_Port=80;

	m_DiscIDWrapper.FromCuesheet(m_Cuesheet);
	if (!m_OverrideDiskID)
		m_DiskID.assign(m_DiscIDWrapper.ID());
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

	MusicBrainz5::CQuery MusicBrainz("flactag-" VERSION,m_Server,m_Port);

	try
	{
		MusicBrainz5::CReleaseList ReleaseList=MusicBrainz.LookupDiscID(m_DiskID);

		if (ReleaseList.NumItems())
		{
			RetVal=true;

			for (int ReleaseNum=0;ReleaseNum<ReleaseList.NumItems();ReleaseNum++)
			{
				MusicBrainz5::CRelease *Release=ReleaseList.Item(ReleaseNum);

				MusicBrainz5::CRelease FullRelease=MusicBrainz.LookupRelease(Release->ID());

				MusicBrainz5::CMediumList MediaList=FullRelease.MediaMatchingDiscID(m_DiskID);
	 			for (int MediumNumber=0;MediumNumber<MediaList.NumItems();MediumNumber++)
				{
					MusicBrainz5::CMedium *Medium=MediaList.Item(MediumNumber);

					CAlbum Album=ParseAlbum(FullRelease,Medium);

					MusicBrainz5::CTrackList *TrackList=Medium->TrackList();
					if (TrackList)
					{
						for (int TrackNumber=0;TrackNumber<TrackList->NumItems();TrackNumber++)
						{
							MusicBrainz5::CTrack *MBTrack=TrackList->Item(TrackNumber);

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

	catch (MusicBrainz5::CResourceNotFoundError Exception)
	{
			std::stringstream os;
			os << "No albums found for file '" << FlacFile << "'";
			CErrorLog::Log(os.str());

			CErrorLog::Log("Please submit the DiskID using the following URL:");
			CErrorLog::Log(m_DiscIDWrapper.SubmitURL());
	}

	catch (MusicBrainz5::CExceptionBase Exception)
	{
		std::cerr << FlacFile << ": Exception: " << Exception.what() << std::endl;
	}

	return RetVal;
}

CCoverArt CMusicBrainzInfo::GetCoverArt(const CUTF8Tag &ReleaseID, const CUTF8Tag &ASIN)
{
	CCoverArtFetch CoverArtFetch(ReleaseID.DisplayValue(), ASIN.DisplayValue());
	return CoverArtFetch.CoverArt();
}

CAlbum CMusicBrainzInfo::ParseAlbum(const MusicBrainz5::CRelease& Release, const MusicBrainz5::CMedium* Medium)
{
	CAlbum Album;

	if (!Release.Title().empty())
	{
		Album.SetName(Release.Title());
		if (m_ConfigFile.BoolValue(CConfigFile::tConfigEntry::IncludeAlbumDisambiguation) && !Release.Disambiguation().empty())
		{
			Album.SetName(Album.Name() + std::string(" (") + Release.Disambiguation() + std::string(")"));
		}
	}
	else if (Release.ReleaseGroup() && !Release.ReleaseGroup()->Title().empty())
	{
		Album.SetName(Release.ReleaseGroup()->Title());
		if (m_ConfigFile.BoolValue(CConfigFile::tConfigEntry::IncludeAlbumDisambiguation) && !Release.ReleaseGroup()->Disambiguation().empty())
		{
			Album.SetName(Album.Name() + std::string(" (") + Release.ReleaseGroup()->Disambiguation() + std::string(")"));
		}
	}

	if (Release.MediumList() && Release.MediumList()->NumItems()>1)
		Album.SetDiskNumber(Medium->Position());

	Album.SetAlbumID(Release.ID());

	MusicBrainz5::CArtistCredit *ArtistCredit=Release.ArtistCredit();
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

	Album.SetCoverArt(GetCoverArt(Release.ID(), Album.ASIN()));

	if (Release.ReleaseGroup())
			Album.SetType(AlbumType(Release.ReleaseGroup()->PrimaryType()));

	Album.SetStatus(AlbumStatus(Release.Status()));

	std::string AlbumDate=Release.Date();

	std::string::size_type MinusPos=AlbumDate.find("-");
	if (std::string::npos!=MinusPos)
		AlbumDate=AlbumDate.substr(0,MinusPos);

	Album.SetDate(AlbumDate);

	return Album;
}

void CMusicBrainzInfo::ParseArtist(const MusicBrainz5::CArtistCredit* ArtistCredit, std::string& ArtistID, std::string& ArtistName, std::string& ArtistSort)
{
	bool FirstArtist=true;

	MusicBrainz5::CNameCreditList *NameCreditsList=ArtistCredit->NameCreditList();
	if (NameCreditsList)
	{
		for (int NameCreditNumber=0;NameCreditNumber<NameCreditsList->NumItems();NameCreditNumber++)
		{
			MusicBrainz5::CNameCredit *NameCredit=NameCreditsList->Item(NameCreditNumber);

			MusicBrainz5::CArtist *Artist=NameCredit->Artist();

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

CTrack CMusicBrainzInfo::ParseTrack(const MusicBrainz5::CTrack* MBTrack)
{
	CTrack Track;

	Track.SetNumber(MBTrack->Position());

	if (!MBTrack->Title().empty())
		Track.SetName(MBTrack->Title());
	else if (MBTrack->Recording())
		Track.SetName(MBTrack->Recording()->Title());

	if (MBTrack->Recording())
	{
		MusicBrainz5::CArtistCredit *ArtistCredit=MBTrack->Recording()->ArtistCredit();
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


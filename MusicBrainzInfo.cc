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

#include <musicbrainz3/query.h>
#include <musicbrainz3/filters.h>
#include <musicbrainz3/release.h>
#include <musicbrainz3/webservice.h>
#include <musicbrainz3/utils.h>

extern "C"
{
#include <http_fetcher.h>
}

#include "base64.h"

#include "DiscIDWrapper.h"
#include "ErrorLog.h"

CMusicBrainzInfo::CMusicBrainzInfo(const CCuesheet& Cuesheet)
:	m_Cuesheet(Cuesheet)
{
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

	MusicBrainz::Query Query;

	try
	{
		WaitRequest();

		MusicBrainz::ReleaseResultList Releases=Query.getReleases(&MusicBrainz::ReleaseFilter().discId(DiskID));

		if (Releases.size())
		{
			RetVal=true;

			for (MusicBrainz::ReleaseResultList::size_type count=0; count<Releases.size(); count++)
			{
				try
				{
					WaitRequest();
					MusicBrainz::Release *Release =
					Query.getReleaseById(Releases[count]->getRelease()->getId(),
					&MusicBrainz::ReleaseIncludes().tracks().artist().releaseEvents().urlRelations());

					CAlbum Album;

					std::string AlbumName=Release->getTitle();
					std::string::size_type DiskNumPos=AlbumName.find(" (disc ");
					if (std::string::npos!=DiskNumPos)
					{
						int DiskNumber;
						std::string NumStr=AlbumName.substr(DiskNumPos+7);
						AlbumName=AlbumName.substr(0,DiskNumPos);
						std::stringstream os;
						os << NumStr;
						os >> DiskNumber;
						Album.SetDiskNumber(DiskNumber);
					}

					Album.SetName(AlbumName);

					Album.SetAlbumID(MusicBrainz::extractUuid(Release->getId()));

					Album.SetArtist(Release->getArtist()->getName());
					Album.SetArtistSort(Release->getArtist()->getSortName());
					Album.SetArtistID(MusicBrainz::extractUuid(Release->getArtist()->getId()));

					Album.SetASIN(Release->getAsin());

					if (!Album.ASIN().empty())
					{
						std::string URL="http://images.amazon.com/images/P/" + Album.ASIN().DisplayValue() + ".02.LZZZZZZZ.jpg";

						char *Buffer=0;

						int Bytes=http_fetch(URL.c_str(),&Buffer);
						if (Bytes<1000)
						{
							free(Buffer);
							Buffer=0;
							URL="http://images.amazon.com/images/P/" + Album.ASIN().DisplayValue() + ".02.MZZZZZZZ.jpg";
							Bytes=http_fetch(URL.c_str(),&Buffer);
						}

						if (Bytes>0)
						{
							if (Bytes<1000)
								CErrorLog::Log("Album art downloaded was less than 1000 bytes, ignoring");
							else
								Album.SetCoverArt(CCoverArt((const unsigned char *)Buffer,Bytes));
						}
						else
							CErrorLog::Log(std::string("Error downloading art: ") + http_strerror());

						if (Buffer)
							free(Buffer);
					}

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

					MusicBrainz::TrackList Tracks=Release->getTracks();

					for (MusicBrainz::TrackList::size_type i=0; i<Tracks.size(); i++)
					{
						CTrack Track;

						Track.SetNumber(i+1);
						Track.SetName(Tracks[i]->getTitle());
						if (Tracks[i]->getArtist())
						{
							Track.SetArtist(Tracks[i]->getArtist()->getName());
							Track.SetArtistSort(Tracks[i]->getArtist()->getSortName());
							Track.SetArtistID(MusicBrainz::extractUuid(Tracks[i]->getArtist()->getId()));
						}
						else
						{
							Track.SetArtist(Release->getArtist()->getName());
							Track.SetArtistSort(Release->getArtist()->getSortName());
							Track.SetArtistID(MusicBrainz::extractUuid(Release->getArtist()->getId()));
						}

						Track.SetTrackID(MusicBrainz::extractUuid(Tracks[i]->getId()));

						Album.AddTrack(Track);
					}

					MusicBrainz::ReleaseEventList ReleaseEvents = Release->getReleaseEvents();

					if (ReleaseEvents.size())
					{
						std::string AlbumDate=ReleaseEvents[0]->getDate();
						std::string::size_type MinusPos=AlbumDate.find("-");
						if (std::string::npos!=MinusPos)
							AlbumDate=AlbumDate.substr(0,MinusPos);

						if (!AlbumDate.empty())
							Album.SetDate(AlbumDate);
					}

					m_Albums.push_back(Album);

					delete Release;
				}

				catch (MusicBrainz::ConnectionError Error)
				{
					RetVal=false;
					CErrorLog::Log(std::string("Connection error from getReleaseById: ") + Error.what());
				}
				catch (MusicBrainz::ValueError Error)
				{
					RetVal=false;
					CErrorLog::Log(std::string("Value error from getReleaseById: ") + Error.what());
				}
/*
				catch (MusicBrainz::ParseError Error)
				{
					RetVal=false;
					CErrorLog::Log(std::string("Parse error from getReleaseById: ") + Error.what());
				}
*/
				catch (MusicBrainz::RequestError Error)
				{
					RetVal=false;
					CErrorLog::Log(std::string("Request error from getReleaseById: ") + Error.what());
				}

				catch (MusicBrainz::ResponseError Error)
				{
					RetVal=false;
					CErrorLog::Log(std::string("Response error from getReleaseById: ") + Error.what());
				}

				catch (MusicBrainz::ResourceNotFoundError Error)
				{
					RetVal=false;
					CErrorLog::Log(std::string("Resource not found error from getReleaseById: ") + Error.what());
				}

				catch (MusicBrainz::DiscError Error)
				{
					RetVal=false;
					CErrorLog::Log(std::string("Disc error from getReleaseById: ") + Error.what());
				}

				catch (MusicBrainz::TimeOutError Error)
				{
					RetVal=false;
					CErrorLog::Log(std::string("TimeOut error from getReleaseById: ") + Error.what());
				}

				catch (MusicBrainz::AuthenticationError Error)
				{
					RetVal=false;
					CErrorLog::Log(std::string("Authentication error from getReleaseById: ") + Error.what());
				}

				catch (MusicBrainz::WebServiceError Error)
				{
					RetVal=false;
					CErrorLog::Log(std::string("WebService error from getReleaseById: ") + Error.what());
				}

				delete Releases[count];
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
	}//catch exceptions from getReleases

	catch (MusicBrainz::ConnectionError Error)
	{
		RetVal=false;
		CErrorLog::Log(std::string("Connection error from getReleases: ") + Error.what());
	}

	catch (MusicBrainz::ValueError Error)
	{
		RetVal=false;
		CErrorLog::Log(std::string("ValueError error from getReleases: ") + Error.what());
	}
/*
	catch (MusicBrainz::ParseError Error)
	{
		RetVal=false;
		CErrorLog::Log(std::string("ParseError error from getReleases: ") + Error.what());
	}
*/
	catch (MusicBrainz::RequestError Error)
	{
		RetVal=false;
		CErrorLog::Log(std::string("RequestError error from getReleases: ") + Error.what());
	}

	catch (MusicBrainz::ResponseError Error)
	{
		RetVal=false;
		CErrorLog::Log(std::string("ResponseError error from getReleases: ") + Error.what());
	}

	catch (MusicBrainz::WebServiceError Error)
	{
		RetVal=false;
		CErrorLog::Log(std::string("Web service error from getReleases: ") + Error.what());
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

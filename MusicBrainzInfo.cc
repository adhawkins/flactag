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

#include <musicbrainz/musicbrainz.h>

extern "C"
{
#include <http_fetcher.h>
}

#include "base64.h"

#include "DiskIDCalculate.h"
#include "ErrorLog.h"

CMusicBrainzInfo::CMusicBrainzInfo(const CCuesheet& Cuesheet)
:	m_Cuesheet(Cuesheet)
{
}

bool CMusicBrainzInfo::LoadInfo(const std::string& FlacFile)
{
	bool RetVal=false;
	
	CDiskIDCalculate Calc(m_Cuesheet);
	std::string DiskID=Calc.DiskID();
	
	//Test Disk ID for album title containing extended characters
	//DiskID="5EgKduVn7sQH9JGg8JQyrPOjSqc-";
	
	//CErrorLog::Log("DiskID: " + DiskID);
	//CErrorLog::Log("Submit: " + Calc.SubmitURL());
			
  MusicBrainz o;
  bool Ret;

  o.UseUTF8(false);

	//o.SetDebug(1);
	//o.SetDepth(5);
	
  vector<string> Args;
  Args.push_back(DiskID);
  Ret=o.Query(string(MBQ_GetCDInfoFromCDIndexId),&Args);

  if (Ret)
  {
  	int NumAlbums=o.DataInt(MBE_GetNumAlbums);
    if (NumAlbums)
    {
    	RetVal=true;
    	
	    for (int count=0; count<NumAlbums; count++)
	    {
		    o.Select(MBS_SelectAlbum, count+1);
	
				CAlbum Album;
				
				std::string AlbumName=o.Data(MBE_AlbumGetAlbumName);
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
				Album.SetArtist(o.Data(MBE_AlbumGetAlbumArtistName));
				Album.SetArtistSort(o.Data(MBE_AlbumGetAlbumArtistSortName));
				Album.SetASIN(o.Data(MBE_AlbumGetAmazonAsin));

				if (!Album.ASIN().empty())
				{				
					std::string URL="http://images.amazon.com/images/P/" + Album.ASIN() + ".02.LZZZZZZZ.jpg";
												
					char *Buffer=0;
					
					int Bytes=http_fetch(URL.c_str(),&Buffer);
					if (Bytes<1000)
					{
						free(Buffer);
						Buffer=0;
						URL="http://images.amazon.com/images/P/" + Album.ASIN() + ".02.MZZZZZZZ.jpg";
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
				
				std::string Status;
				o.GetFragmentFromURL(o.Data(MBE_AlbumGetAlbumStatus),Status);
				Album.SetStatus(AlbumStatus(Status));
				
				std::string Type;
				o.GetFragmentFromURL(o.Data(MBE_AlbumGetAlbumType),Type);
				Album.SetType(AlbumType(Type));
	
				std::string ArtistID;
				o.GetIDFromURL(o.Data(MBE_AlbumGetAlbumArtistId),ArtistID);
				Album.SetArtistID(ArtistID);
				
				std::string AlbumID;
				o.GetIDFromURL(o.Data(MBE_AlbumGetAlbumId),AlbumID);
				Album.SetAlbumID(AlbumID);

		    int NumTracks=o.DataInt(MBE_AlbumGetNumTracks);

				for (int i=1; i<=NumTracks; i++)
		    {
		    	CTrack Track;
		    	
		    	Track.SetNumber(i);
		    	Track.SetName(o.Data(MBE_AlbumGetTrackName,i));
		    	Track.SetArtist(o.Data(MBE_AlbumGetArtistName,i));
		    	Track.SetArtistSort(o.Data(MBE_AlbumGetArtistSortName,i));
		    	
		    	std::string ArtistID;
		    	o.GetIDFromURL(o.Data(MBE_AlbumGetArtistId,i),ArtistID);
		    	Track.SetArtistID(ArtistID);
		    	
		    	std::string TrackID;
		    	o.GetIDFromURL(o.Data(MBE_AlbumGetTrackId,i),TrackID);
		    	Track.SetTrackID(TrackID);
		    	
					Album.AddTrack(Track);
				}

				o.Select(MBS_SelectReleaseDate,1);				
				
				std::string AlbumDate=o.Data(MBE_ReleaseGetDate).c_str();
				std::string::size_type MinusPos=AlbumDate.find("-");
				if (std::string::npos!=MinusPos)
					AlbumDate=AlbumDate.substr(0,MinusPos);

				if (!AlbumDate.empty())
					Album.SetDate(AlbumDate);
				
				m_Albums.push_back(Album);

				o.Select(MBS_Rewind);
			}
		}
		else
		{
			std::stringstream os;
			os << "No albums found for file '" << FlacFile << "'";
			CErrorLog::Log(os.str());
			
			CErrorLog::Log("Please submit the DiskID using the following URL:");
			CErrorLog::Log(Calc.SubmitURL());
		}
  }
  else
  {
  	std::string Error;
  		
		o.GetQueryError(Error);
		
		std::stringstream os;
		os << "Query failed: " << Error;
		CErrorLog::Log(os.str());
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
		if (Type.length()>4 && strcasecmp(Type.substr(4).c_str(),AlbumTypeStrings[i])==0)
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
		if (Status.length()>6 && strcasecmp(Status.substr(6).c_str(),AlbumStatusStrings[i])==0)
		{
			Ret=AlbumStatusStrings[i];
			break;
		}
		
		++i;
	}	
	
	return Ret;
}

#include "MusicBrainzInfo.h"

#include <sstream>

#include <musicbrainz/musicbrainz.h>

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
	
				std::string AlbumName=o.Data(MBE_AlbumGetAlbumName);
				std::string AlbumArtist=o.Data(MBE_AlbumGetAlbumArtistName);
				std::string AlbumArtistSort=o.Data(MBE_AlbumGetAlbumArtistSortName);
				std::string AlbumAsin=o.Data(MBE_AlbumGetAmazonAsin);

				CAlbum Album;
				
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
				Album.SetArtist(AlbumArtist);
				Album.SetArtistSort(AlbumArtistSort);
				Album.SetAsin(AlbumAsin);
	
		    int NumTracks=o.DataInt(MBE_AlbumGetNumTracks);

		    o.Select(MBS_SelectAlbum, count+1);
	
				for (int i=1; i<=NumTracks; i++)
		    {
		    	CTrack Track;
		    	
		    	Track.SetNumber(i);
		    	Track.SetName(o.Data(MBE_AlbumGetTrackName,i));
		    	Track.SetArtist(o.Data(MBE_AlbumGetArtistName,i));
		    	Track.SetArtistSort(o.Data(MBE_AlbumGetArtistSortName,i));
		    	
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

	

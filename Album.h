#ifndef _ALBUM_H
#define _ALBUM_H

#include <string>
#include <vector>

#include "Track.h"

class CAlbum
{
public:
	CAlbum();
	
	void AddTrack(const CTrack& Track);
	std::string Name() const;
	std::string Artist() const;
	std::string ArtistSort() const;
	std::string Date() const;
	std::string Asin() const;
	std::vector<CTrack> Tracks() const;
	int DiskNumber() const;
		
	void SetDate(const std::string& Date);
	void SetName(const std::string& Name);
	void SetArtist(const std::string& Artist);
	void SetArtistSort(const std::string& ArtistSort);
	void SetAsin(const std::string& Asin);
	void SetDiskNumber(int DiskNumber);
	
private:
	std::vector<CTrack> m_Tracks;
	std::string m_Name;
	std::string m_Artist;
	std::string m_ArtistSort;
	std::string m_Date;
	std::string m_Asin;
	int m_DiskNumber;
};

#endif

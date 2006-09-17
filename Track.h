#ifndef _TRACK_H
#define _TRACK_H

#include <string>

#include <FLAC++/metadata.h>

class CTrack
{
public:
	CTrack();

	FLAC__byte Number() const;
	std::string Name() const;
	std::string Artist() const;
	std::string ArtistSort() const;
		
	void SetNumber(FLAC__byte Number);
	void SetName(const std::string& Name);
	void SetArtist(const std::string& Artist);
	void SetArtistSort(const std::string& ArtistSort);
		
		
private:
	FLAC__byte m_Number;
	std::string m_Name;
	std::string m_Artist;
	std::string m_ArtistSort;
};

#endif

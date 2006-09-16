#ifndef _ALBUM_H
#define _ALBUM_H

#include <string>
#include <vector>

#include "Track.h"

class CAlbum
{
public:
	CAlbum(const std::string& Name, const std::string& Artist, const std::string& Date="");
	
	void AddTrack(const CTrack& Track);
	std::string Name() const;
	std::string Artist() const;
	std::string Date() const;
	std::vector<CTrack> Tracks() const;
		
	void SetDate(const std::string& Date);
	
private:
	std::vector<CTrack> m_Tracks;
	std::string m_Name;
	std::string m_Artist;
	std::string m_Date;
};

#endif

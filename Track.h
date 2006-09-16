#ifndef _TRACK_H
#define _TRACK_H

#include <string>

class CTrack
{
public:
	CTrack(int Number, const std::string& Name, const std::string& Artist);

	int Number() const;
	std::string Name() const;
	std::string Artist() const;
		
private:
	int m_Number;
	std::string m_Name;
	std::string m_Artist;
};

#endif

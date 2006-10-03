#ifndef _COVERART_H
#define _COVERART_H

#include <string.h>

#include <string>

class CCoverArt
{
public:
	CCoverArt(const unsigned char *Data=0, size_t Length=0);
	CCoverArt(const CCoverArt& Other);
	~CCoverArt();
	
	CCoverArt& operator =(const CCoverArt& Other);

	void SetArt(const unsigned char *Data, size_t Length);
	operator std::string() const;
		
private:
	void Free();
	
	unsigned char *m_Data;
	size_t m_Length;
};

#endif

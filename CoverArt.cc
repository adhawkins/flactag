#include "CoverArt.h"

#include "base64.h"

CCoverArt::CCoverArt(const unsigned char *Data, size_t Length)
:	m_Data(0),
	m_Length(0)
{
	SetArt(Data,Length);
}

CCoverArt::CCoverArt(const CCoverArt& Other)
:	m_Data(0),
	m_Length(0)
{
	if (this!=&Other)
		*this=Other;
}

CCoverArt::~CCoverArt()
{
	Free();
}

void CCoverArt::Free()
{
	if (m_Data)
		delete[] m_Data;
		
	m_Data=0;
	m_Length=0;
}

CCoverArt& CCoverArt::operator =(const CCoverArt& Other)
{
	SetArt(Other.m_Data,Other.m_Length);
	
	return *this;
}

CCoverArt::operator std::string() const
{
	return rfc822_binary(m_Data,m_Length);
}

void CCoverArt::SetArt(const unsigned char *Data, size_t Length)
{	
	Free();
	
	if (Data && Length)
	{
		m_Data=new unsigned char[Length];
		m_Length=Length;
		memcpy(m_Data,Data,Length);
	}
}


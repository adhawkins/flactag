#include "Track.h"

CTrack::CTrack(int Number, const std::string& Name, const std::string& Artist)
:	m_Number(Number),
	m_Name(Name),
	m_Artist(Artist)
{
}

std::string CTrack::Artist() const
{
	return m_Artist;
}

std::string CTrack::Name() const
{
	return m_Name;
}

int CTrack::Number() const
{
	return m_Number;
}

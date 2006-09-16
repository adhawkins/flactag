#include "Album.h"

CAlbum::CAlbum(const std::string& Name, const std::string& Artist, const std::string& Date)
:	m_Name(Name),
	m_Artist(Artist),
	m_Date(Date)
{
}

void CAlbum::AddTrack(const CTrack& Track)
{
	m_Tracks.push_back(Track);
}

std::string CAlbum::Name() const
{
	return m_Name;
}

std::string CAlbum::Artist() const
{
	return m_Artist;
}

std::string CAlbum::Date() const
{
	return m_Date;
}

std::vector<CTrack> CAlbum::Tracks() const
{
	return m_Tracks;
}

void CAlbum::SetDate(const std::string& Date)
{
	m_Date=Date;
}
	

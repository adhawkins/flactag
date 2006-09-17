#include "Track.h"

CTrack::CTrack()
:	m_Number(255)
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

FLAC__byte CTrack::Number() const
{
	return m_Number;
}

std::string CTrack::ArtistSort() const
{
	return m_ArtistSort;
}
	
void CTrack::SetNumber(FLAC__byte Number)
{
	m_Number=Number;
}

void CTrack::SetName(const std::string& Name)
{
	m_Name=Name;
}

void CTrack::SetArtist(const std::string& Artist)
{
	m_Artist=Artist;
}
void CTrack::SetArtistSort(const std::string& ArtistSort)
{
	m_ArtistSort=ArtistSort;
}

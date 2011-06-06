#include "WriteInfo.h"

CWriteInfo::CWriteInfo(const tTagMap& Tags, const CCoverArt& CoverArt)
: m_CoverArt(CoverArt),
	m_Tags(Tags)
{
}

bool CWriteInfo::operator ==(const CWriteInfo& Other) const
{
	return m_Tags==Other.m_Tags && m_CoverArt==Other.m_CoverArt;
}

void CWriteInfo::SetTags(const tTagMap& Tags)
{
	m_Tags=Tags;
}

void CWriteInfo::SetCoverArt(const CCoverArt& CoverArt)
{
	m_CoverArt=CoverArt;
}

tTagMap CWriteInfo::Tags() const
{
	return m_Tags;
}

CCoverArt CWriteInfo::CoverArt() const
{
	return m_CoverArt;
}

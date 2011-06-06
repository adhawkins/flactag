#ifndef _WRITE_INFO_H
#define _WRITE_INFO_H

#include "TagName.h"
#include "CoverArt.h"
#include "UTF8Tag.h"

class CWriteInfo
{
public:
	CWriteInfo(const tTagMap& Tags=tTagMap(), const CCoverArt& CoverArt=CCoverArt());
	
	bool operator ==(const CWriteInfo& Other) const;

	void SetTags(const tTagMap& Tags);
	void SetCoverArt(const CCoverArt& CoverArt);
	
	tTagMap Tags() const;
	CCoverArt CoverArt() const;
	
private:
	CCoverArt m_CoverArt;
	tTagMap m_Tags;
};

#endif

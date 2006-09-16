#ifndef _FLAC_INFO_H
#define _FLAC_INFO_H

#include <string>

#include <FLAC++/metadata.h>

#include "TagName.h"
#include "Cuesheet.h"

class CFlacInfo
{
public:
	CFlacInfo();
	~CFlacInfo();
	
	void SetFileName(const std::string& FileName);
	bool Read();
	tTagMap Tags() const;
	CCuesheet Cuesheet() const;
	bool CuesheetFound() const;

	bool WriteTags(const tTagMap& Tags);
	void SetTag(const CTagName& Name, const std::string& Value);
	
private:
	int CalculateOffset(const FLAC::Metadata::CueSheet::Track& Track) const;

	std::string m_FileName;
	tTagMap m_Tags;
	CCuesheet m_Cuesheet;
	FLAC::Metadata::Chain m_Chain;
	FLAC::Metadata::VorbisComment *m_TagBlock;
	bool m_CuesheetFound;
};

#endif

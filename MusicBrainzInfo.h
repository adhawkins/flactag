#ifndef _MUSICBRAINZ_INFO_H
#define _MUSICBRAINZ_INFO_H

#include <vector>

#include "Album.h"
#include "Cuesheet.h"

class CMusicBrainzInfo
{
public:
	CMusicBrainzInfo(const CCuesheet& Cuesheet);
	
	bool LoadInfo(const std::string& FlacFile);
	std::vector<CAlbum> Albums() const;
	
private:
	std::vector<CAlbum> m_Albums;
	CCuesheet m_Cuesheet;
};

#endif

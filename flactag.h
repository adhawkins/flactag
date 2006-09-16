#ifndef _FLACTAG_H
#define _FLACTAG_H

#include <string>

#include "Album.h"
#include "TagName.h"
#include "Cuesheet.h"
#include "FlacInfo.h"

class CFlacTag
{
public:
	typedef enum
	{
		eWindow_Albums,
		eWindow_Tracks,
		eWindow_Tags,
	} tWindowType;
	
	CFlacTag(const std::string& FlacFile);
		
private:
	void MainLoop();
	void LoadData(const std::string& FlacFile);

	std::vector<CAlbum> m_Albums;
	CFlacInfo m_FlacInfo;			
	tTagMap m_FlacTags;
	CCuesheet m_FlacCuesheet;
	tTagMap m_WriteTags;
	tWindowType m_SelectedWindow;
};

#endif

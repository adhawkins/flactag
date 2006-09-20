#ifndef _FLACTAG_H
#define _FLACTAG_H

#include <string>

#include "Album.h"
#include "TagName.h"
#include "Cuesheet.h"
#include "FlacInfo.h"
#include "ConfigFile.h"

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
	bool LoadData();
	bool MakeDirectoryTree(const std::string& Directory) const;
	bool CheckMakeDirectory(const std::string& Directory) const;
	bool MakeDirectory(const std::string& Directory, mode_t Mode) const;
	void RenameFile();
	bool CopyFile(const std::string& SourceFile, const std::string& DestFile) const;
	
	std::string m_FlacFile;
	std::vector<CAlbum> m_Albums;
	CFlacInfo m_FlacInfo;			
	tTagMap m_FlacTags;
	CCuesheet m_FlacCuesheet;
	tTagMap m_WriteTags;
	tWindowType m_SelectedWindow;
	CConfigFile m_ConfigFile;
	std::string m_RenameFile;
};

#endif

#ifndef _FILENAME_BUILDER_H
#define _FILENAME_BUILDER_H

#include <string>

#include "TagName.h"

class CFileNameBuilder
{
public:
	CFileNameBuilder(const tTagMap& m_Tags, const std::string& BasePath, const std::string& SingleDiskFileName, const std::string& MultiDiskFileName);
	
	std::string FileName() const;
private:
	void BuildPath();
	void ReplaceString(const std::string& Search, const std::string& ReplaceTag);

	tTagMap m_Tags;
	std::string m_BasePath;
	std::string m_SingleDiskFileName;
	std::string m_MultiDiskFileName;
	std::string m_FileName;
};

#endif

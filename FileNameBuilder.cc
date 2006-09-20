#include "FileNameBuilder.h"

CFileNameBuilder::CFileNameBuilder(const tTagMap& Tags, const std::string& BasePath, const std::string& SingleDiskFileName, const std::string& MultiDiskFileName)
:	m_Tags(Tags),
	m_BasePath(BasePath),
	m_SingleDiskFileName(SingleDiskFileName),
	m_MultiDiskFileName(MultiDiskFileName)
{
	BuildPath();
}
	
std::string CFileNameBuilder::FileName() const
{
	return m_FileName;
}

void CFileNameBuilder::BuildPath()
{
	std::string Template;
	
	if (m_Tags[CTagName("DISCNUMBER")].empty())
		Template=m_SingleDiskFileName;
	else
		Template=m_MultiDiskFileName;
		
	m_FileName=m_BasePath+"/"+Template;
	
	ReplaceString("%A","ARTIST");
	ReplaceString("%S","ARTISTSORT");
	ReplaceString("%T","ALBUM");
	ReplaceString("%D","DISCNUMBER");
	ReplaceString("%Y","YEAR");
	ReplaceString("%G","GENRE");
}

void CFileNameBuilder::ReplaceString(const std::string& Search, const std::string& ReplaceTag)
{
	std::string Replace="NO"+ReplaceTag;
	
	tTagMap::const_iterator ThisTag=m_Tags.find(CTagName(ReplaceTag));
	if (m_Tags.end()!=ThisTag)
		Replace=(*ThisTag).second;
	
	//printf("'%s': Replacing '%s' with '%s' (%s)\n",m_FileName.c_str(),Search.c_str(),ReplaceTag.c_str(),Replace.c_str());
	
	std::string::size_type SearchPos=m_FileName.find(Search);
	while(std::string::npos!=SearchPos)
	{
		m_FileName=m_FileName.substr(0,SearchPos)+Replace+m_FileName.substr(SearchPos+Search.length());
		SearchPos=m_FileName.find(Search);
	}
		
	//printf("'%s'\n",m_FileName.c_str());
}

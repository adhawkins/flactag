#ifndef _CONFIG_FILE_H
#define _CONFIG_FILE_H

#include <map>
#include <string>

class CConfigFile
{
public:
	CConfigFile();

	bool LoadFile(const std::string& FileName);
	bool SaveFile(const std::string& FileName) const;
		
	std::string Value(const std::string& Name) const;
			
private:
	std::map<std::string,std::string> m_Values;
};

#endif


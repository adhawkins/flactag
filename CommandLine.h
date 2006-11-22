#ifndef _COMMAND_LINE_H
#define _COMMAND_LINE_H

#include <string>
#include <vector>

class CCommandLine
{
public:
	CCommandLine(int argc, char *const argv[]);
	
	bool Valid() const;
	bool Check() const;
	bool Write() const;
	bool Rename() const;
	bool ForceMulti() const;
	bool Version() const;
	bool DiscID() const;
	std::vector<std::string> FileNames() const;
	
private:
	bool m_Valid;
	bool m_Check;
	bool m_Write;
	bool m_Rename;
	bool m_ForceMulti;
	bool m_Version;
	bool m_DiscID;
	std::vector<std::string> m_FileNames;
		
	void Usage(const std::string& ProgName) const;
};

#endif

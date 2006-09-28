#ifndef _COMMAND_LINE_H
#define _COMMAND_LINE_H

#include <string>

class CCommandLine
{
public:
	CCommandLine(int argc, char *const argv[]);
	
	bool Valid() const;
	bool Check() const;
	bool Write() const;
	bool Cover() const;
	bool Rename() const;
	bool ForceMulti() const;
	std::string FileName() const;
	
private:
	bool m_Valid;
	bool m_Check;
	bool m_Write;
	bool m_Cover;
	bool m_Rename;
	bool m_ForceMulti;
	std::string m_FileName;
		
	void Usage(const std::string& ProgName) const;
};

#endif

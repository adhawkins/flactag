#ifndef _COMMAND_LINE_H
#define _COMMAND_LINE_H

#include <string>

class CCommandLine
{
public:
	CCommandLine(int argc, char *const argv[]);
	
	bool Check() const;
	bool Apply() const;
	std::string FileName() const;
	
private:
	bool m_Check;
	bool m_Apply;
	std::string m_FileName;
};

#endif

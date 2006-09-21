#ifndef _ERROR_LOG_H
#define _ERROR_LOG_H

#include <string>
#include <vector>

class CErrorLog
{
public:
	static void Log(const std::string& String);
	static void DumpLog();
	
	static const std::vector<std::string>::size_type m_cMaxSize;
};

#endif


#include "ErrorLog.h"

const std::vector<std::string>::size_type CErrorLog::m_cMaxSize=100;
	
std::vector<std::string> Entries;
	
void CErrorLog::Log(const std::string& String)
{
	Entries.push_back(String);
	
	while (Entries.size()>m_cMaxSize)
		Entries.erase(Entries.begin());
}

void CErrorLog::DumpLog()
{
	std::vector<std::string>::const_iterator ThisEntry=Entries.begin();
	while (Entries.end()!=ThisEntry)
	{
		fprintf(stderr,"%s\n",(*ThisEntry).c_str());
		
		++ThisEntry;
	}
}


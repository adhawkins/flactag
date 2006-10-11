#include "CommandLine.h"

#include <sstream>

#include <getopt.h>

#include "ErrorLog.h"

CCommandLine::CCommandLine(int argc, char *const argv[])
:	m_Valid(true),
	m_Check(false),
	m_Write(false),
	m_Rename(false),
	m_ForceMulti(false),
	m_Version(false)
{
	struct option LongOptions[] =
	{
		{"version", no_argument, 0, 'v'},
		{"force-multi", no_argument, 0, 'm'},
		{"rename", no_argument, 0, 'r'},
		{"write", no_argument, 0, 'w'},
		{"check", no_argument, 0, 'c'},
		{0, 0, 0, 0}
	};
             
	int OptionIndex=0;
	int Ret;

	opterr=1;
		
	do
	{
		Ret=getopt_long(argc,argv,"vmrwc",LongOptions,&OptionIndex);
		switch (Ret)
		{
			case 'v':
				m_Version=true;
				break;
				
			case 'm':
				m_ForceMulti=true;
				break;
				
			case 'r':
				m_Rename=true;
				break;
				
			case 'w':
				m_Write=true;
				break;
				
			case 'c':
				m_Check=true;
				break;

			case -1:
				//Reached end of options
				break;
				
			default:
				m_Valid=false;
				break;
		}
	} while (m_Valid && -1!=Ret);

	if (m_Valid)
	{	
		int LastArg=optind;
		
		while (LastArg!=argc)
		{
			m_FileNames.push_back(argv[LastArg]);
			LastArg++;
		}
		
		if (m_FileNames.empty() && !m_Version)
			m_Valid=false;
	}
	
	if (!m_Valid)
		Usage(argv[0]);
}

bool CCommandLine::Valid() const
{
	return m_Valid;
}

bool CCommandLine::Check() const
{
	return m_Check;
}

bool CCommandLine::Write() const
{
	return m_Write;
}

bool CCommandLine::Rename() const
{
	return m_Rename;
}

bool CCommandLine::ForceMulti() const
{
	return m_ForceMulti;
}

bool CCommandLine::Version() const
{
	return m_Version;
}

std::vector<std::string> CCommandLine::FileNames() const
{
	return m_FileNames;
}

void CCommandLine::Usage(const std::string& ProgName) const
{
	printf("Usage: %s [ --version | -v ] [ --check | -c ] [ --write | -w ]\n"
					"\t\t[ --rename | -r ] [ --force-multi | -m ]\n"
					"\t\tflacfile [ flacfile ] [ flacfile ]\n",ProgName.c_str());
}

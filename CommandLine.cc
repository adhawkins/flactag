#include "CommandLine.h"

#include <sstream>

#include <getopt.h>

#include "ErrorLog.h"

CCommandLine::CCommandLine(int argc, char *const argv[])
:	m_Valid(true),
	m_Check(false),
	m_Write(false),
	m_Cover(false),
	m_Rename(false),
	m_ForceMulti(false)
{
	struct option LongOptions[] =
	{
		{"force-multi", no_argument, 0, 'm'},
		{"rename", no_argument, 0, 'r'},
		{"cover", no_argument, 0, 'v'},
		{"write", no_argument, 0, 'w'},
		{"check", no_argument, 0, 'c'},
		{0, 0, 0, 0}
	};
             
	int OptionIndex=0;
	int Ret;

	opterr=1;
		
	do
	{
		Ret=getopt_long(argc,argv,"mrvwc",LongOptions,&OptionIndex);
		switch (Ret)
		{
			case 'm':
				m_ForceMulti=true;
				break;
				
			case 'r':
				m_Rename=true;
				break;
				
			case 'v':
				m_Cover=true;
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
		
		if (m_FileNames.empty())
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

bool CCommandLine::Cover() const
{
	return m_Cover;
}

bool CCommandLine::Rename() const
{
	return m_Rename;
}

bool CCommandLine::ForceMulti() const
{
	return m_ForceMulti;
}

std::vector<std::string> CCommandLine::FileNames() const
{
	return m_FileNames;
}

void CCommandLine::Usage(const std::string& ProgName) const
{
	printf("Usage: %s [ --check | -c ] [ --write | -w ] [ --rename | -r ]\n"
					"\t\t[ --cover | -v ] [ --force-multi | -m ]\n"
					"\t\tflacfile [ flacfile ] [ flacfile ]\n",ProgName.c_str());
}

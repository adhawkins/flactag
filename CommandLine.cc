#include "CommandLine.h"

#include <sstream>

#include <getopt.h>

#include "ErrorLog.h"

CCommandLine::CCommandLine(int argc, char *const argv[])
:	m_Check(false),
	m_Apply(false)
{
	struct option LongOptions[] =
	{
		{"apply", no_argument, 0, 'a'},
		{"check", no_argument, 0, 'c'},
		{"filename", required_argument, 0, 'f'},
		{0, 0, 0, 0}
	};
             
	int OptionIndex=0;
	int Ret;
	
	do
	{
		Ret=getopt_long(argc,argv,"acf:",LongOptions,&OptionIndex);
		switch (Ret)
		{
			case 'a':
				m_Apply=true;
				break;
				
			case 'c':
				m_Check=true;
				break;

			case 'f':
				m_FileName=optarg;
				break;
		}
	} while (-1!=Ret);
}

bool CCommandLine::Check() const
{
	return m_Check;
}

bool CCommandLine::Apply() const
{
	return m_Apply;
}

std::string CCommandLine::FileName() const
{
	return m_FileName;
}

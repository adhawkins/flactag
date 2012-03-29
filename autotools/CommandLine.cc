/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006-2012 Andrew Hawkins
   Copyright (C) 2011-2012 Daniel Pocock

   This file is part of flactag.

   Flactag is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#include "CommandLine.h"

#include <sstream>

#include <stdio.h>
#include <getopt.h>

#include "ErrorLog.h"

CCommandLine::CCommandLine(int argc, char *const argv[])
:	m_Valid(true),
	m_Check(false),
	m_Write(false),
	m_Rename(false),
	m_Version(false),
	m_DiscID(false),
	m_ForceWrite(false),
	m_SubmitURL(false),
	m_OverwriteExisting(false),
	m_OverrideDiscID("")
{
	struct option LongOptions[] =
	{
		{"force-write", no_argument, 0, 'f'},
		{"discid", no_argument, 0, 'd'},
		{"version", no_argument, 0, 'v'},
		{"rename", no_argument, 0, 'r'},
		{"write", no_argument, 0, 'w'},
		{"check", no_argument, 0, 'c'},
		{"submit-url", no_argument, 0, 's'},
		{"overwrite-existing", no_argument, 0, 'o'},
		{"override-discid", required_argument, 0, 'O'},
		{0, 0, 0, 0}
	};

	int OptionIndex=0;
	int Ret;

	opterr=1;

	do
	{
		Ret=getopt_long(argc,argv,"fdvrwcsoO:",LongOptions,&OptionIndex);
		switch (Ret)
		{
			case 's':
				m_SubmitURL=true;
				break;

			case 'f':
				m_ForceWrite=true;
				break;

			case 'd':
				m_DiscID=true;
				break;

			case 'v':
				m_Version=true;
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

			case 'o':
				m_OverwriteExisting=true;
				break;

			case 'O':
				m_OverrideDiscID.assign(optarg);
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
	}

	if (m_FileNames.empty() && !m_Version)
		m_Valid=false;
	else if ((m_FileNames.size() > 1) && (m_OverrideDiscID.size() > 0))
		m_Valid=false;
	else if ((m_DiscID || m_SubmitURL) && (m_Check || m_Write || m_Rename || m_ForceWrite))
		m_Valid=false;
	else if (m_ForceWrite && !m_Write)
		m_Valid=false;

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

bool CCommandLine::Version() const
{
	return m_Version;
}

bool CCommandLine::DiscID() const
{
	return m_DiscID;
}

bool CCommandLine::ForceWrite() const
{
	return m_ForceWrite;
}

bool CCommandLine::SubmitURL() const
{
	return m_SubmitURL;
}

bool CCommandLine::OverwriteExisting() const
{
	return m_OverwriteExisting;
}

bool CCommandLine::OverrideDiscID() const
{
        return m_OverrideDiscID.size() > 0;
}

std::string CCommandLine::OverrideDiscID_val() const
{
	return m_OverrideDiscID;
}

std::vector<std::string> CCommandLine::FileNames() const
{
	return m_FileNames;
}

void CCommandLine::Usage(const std::string& ProgName) const
{
	printf("Usage: %s [ --version | -v ] [ --submit-url | -s ] [ --discid | -d]\n"
					"\t\t[ --check | -c ] [ --write | -w ] [ --force-write | -f ]\n"
					"\t\t[ --rename | -r ] [ --overwrite-existing | -o ]\n"
					"\t\t[ --override-discid discid ]\n"
					"\t\tflacfile [ flacfile ] [ flacfile ]\n",ProgName.c_str());
}

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
	bool Version() const;
	bool DiscID() const;
	bool ForceWrite() const;
	bool SubmitURL() const;
	bool OverwriteExisting() const;
	bool OverrideDiscID() const;
	std::string OverrideDiscID_val() const;
	std::vector<std::string> FileNames() const;

private:
	bool m_Valid;
	bool m_Check;
	bool m_Write;
	bool m_Rename;
	bool m_Version;
	bool m_DiscID;
	bool m_ForceWrite;
	bool m_SubmitURL;
	bool m_OverwriteExisting;
	std::string m_OverrideDiscID;
	std::vector<std::string> m_FileNames;

	void Usage(const std::string& ProgName) const;
};

#endif

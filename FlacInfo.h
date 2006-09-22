/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006 Andrew Hawkins
   
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

#ifndef _FLAC_INFO_H
#define _FLAC_INFO_H

#include <string>

#include <FLAC++/metadata.h>

#include "TagName.h"
#include "Cuesheet.h"

class CFlacInfo
{
public:
	CFlacInfo();
	~CFlacInfo();
	
	void SetFileName(const std::string& FileName);
	bool Read();
	tTagMap Tags() const;
	CCuesheet Cuesheet() const;
	bool CuesheetFound() const;

	bool WriteTags(const tTagMap& Tags);
	void SetTag(const CTagName& Name, const std::string& Value);
	
private:
	int CalculateOffset(const FLAC::Metadata::CueSheet::Track& Track) const;

	std::string m_FileName;
	tTagMap m_Tags;
	CCuesheet m_Cuesheet;
	FLAC::Metadata::Chain m_Chain;
	FLAC::Metadata::VorbisComment *m_TagBlock;
	bool m_CuesheetFound;
};

#endif

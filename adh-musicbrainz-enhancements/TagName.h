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

#ifndef _TAG_NAME_H
#define _TAG_NAME_H

#include <string>
#include <map>

#include "UTF8Tag.h"

class CTagName
{
public:
	CTagName(const std::string& Name, int Number);
	CTagName(const std::string& Name);

	bool operator <(const CTagName& Other) const;
	bool operator >(const CTagName& Other) const;
	bool operator ==(const CTagName& Other) const;
	bool operator !=(const CTagName& Other) const;
	
	std::string Name() const;
	int Number() const;	
	std::string String() const;

private:
	std::string m_Name;
	int m_Number;
	
	bool SpecialTag() const;
};

typedef std::map<CTagName,CUTF8Tag> tTagMap;
typedef tTagMap::const_iterator tTagMapConstIterator;
typedef tTagMap::iterator tTagMapIterator;

#endif

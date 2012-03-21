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

#include "WriteInfo.h"

CWriteInfo::CWriteInfo(const tTagMap& Tags, const CCoverArt& CoverArt)
: m_CoverArt(CoverArt),
	m_Tags(Tags)
{
}

bool CWriteInfo::operator ==(const CWriteInfo& Other) const
{
	return m_Tags==Other.m_Tags && m_CoverArt==Other.m_CoverArt;
}

void CWriteInfo::SetTags(const tTagMap& Tags)
{
	m_Tags=Tags;
}

void CWriteInfo::SetCoverArt(const CCoverArt& CoverArt)
{
	m_CoverArt=CoverArt;
}

tTagMap CWriteInfo::Tags() const
{
	return m_Tags;
}

CCoverArt CWriteInfo::CoverArt() const
{
	return m_CoverArt;
}

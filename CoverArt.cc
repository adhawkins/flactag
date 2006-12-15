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

     $Id: FileNameBuilder.cc 93 2006-12-13 13:12:28Z andy $

----------------------------------------------------------------------------*/

#include "CoverArt.h"

#include "base64.h"

CCoverArt::CCoverArt(const unsigned char *Data, size_t Length)
:	m_Data(0),
	m_Length(0)
{
	SetArt(Data,Length);
}

CCoverArt::CCoverArt(const CCoverArt& Other)
:	m_Data(0),
	m_Length(0)
{
	if (this!=&Other)
		*this=Other;
}

CCoverArt::~CCoverArt()
{
	Free();
}

void CCoverArt::Free()
{
	if (m_Data)
		delete[] m_Data;
		
	m_Data=0;
	m_Length=0;
}

CCoverArt& CCoverArt::operator =(const CCoverArt& Other)
{
	SetArt(Other.m_Data,Other.m_Length);
	
	return *this;
}

CCoverArt::operator std::string() const
{
	return rfc822_binary(m_Data,m_Length);
}

void CCoverArt::SetArt(const unsigned char *Data, size_t Length)
{	
	Free();
	
	if (Data && Length)
	{
		m_Data=new unsigned char[Length];
		m_Length=Length;
		memcpy(m_Data,Data,Length);
	}
}


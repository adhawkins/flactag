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

#include "UTF8Tag.h"

#include <locale.h>
#include <langinfo.h>

CUTF8Tag::CUTF8Tag(const std::string& UTF8Value)
:	m_UTF8Value(UTF8Value)
{
	Convert();
}

void CUTF8Tag::Convert()
{
	if (!m_UTF8Value.empty())
	{
		setlocale(LC_ALL,  "" );
		char *Codeset=nl_langinfo(CODESET);
			
		char *In=new char[m_UTF8Value.length()+1];
		strcpy(In,m_UTF8Value.c_str());
		size_t InLeft=m_UTF8Value.length();
		
		char *Out=new char[m_UTF8Value.length()*4];
		memset(Out,0,m_UTF8Value.length()*4);
		size_t OutLeft=m_UTF8Value.length()*4;
		
		char *InBuff=In;
		char *OutBuff=Out;
		
		iconv_t Convert=iconv_open(Codeset,"UTF-8");
		if ((iconv_t)-1!=Convert)
		{
			if ((size_t)-1!=iconv(Convert,&InBuff,&InLeft,&OutBuff,&OutLeft))
			{
				if (OutLeft>=sizeof(char))
				    *OutBuff='\0';
	
				m_DisplayValue=Out;
			}		    
			
			iconv_close(Convert);
		}
	
		if (In)
			free(In);
			
		if (Out)
			free(Out);
	}
}

bool CUTF8Tag::operator ==(const CUTF8Tag& Other) const
{
	return m_UTF8Value==Other.m_UTF8Value;
}

bool CUTF8Tag::operator !=(const CUTF8Tag& Other) const
{
	return !(*this==Other);
}

bool CUTF8Tag::empty() const
{
	return m_UTF8Value.empty();
}
	
std::string CUTF8Tag::UTF8Value() const
{
	return m_UTF8Value;
}

std::string CUTF8Tag::DisplayValue() const
{
	return m_DisplayValue;
}

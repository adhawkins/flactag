/* --------------------------------------------------------------------------

	 flactag -- A tagger for single album FLAC files with embedded CUE sheets
							using data retrieved from the MusicBrainz service

	 Copyright (C) 2006-2022 Andrew Hawkins

	 This file is part of flactag.

	 This program is free software: you can redistribute it and/or modify
	 it under the terms of the GNU General Public License as published by
	 the Free Software Foundation, either version 3 of the License, or
	 (at your option) any later version.

	 Flactag is distributed in the hope that it will be useful,
	 but WITHOUT ANY WARRANTY; without even the implied warranty of
	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	 Lesser General Public License for more details.

	 You should have received a copy of the GNU General Public
	 License along with this library; if not, write to the Free Software
	 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

		 $Id$

----------------------------------------------------------------------------*/

#include "UTF8Tag.h"

#include <locale.h>
#include <langinfo.h>
#include <unac.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <iconv.h>

#include <sstream>

#include "ErrorLog.h"

CUTF8Tag::CUTF8Tag(const std::string& UTF8Value)
:	m_UTF8Value(UTF8Value)
{
	Convert();
}

void CUTF8Tag::Convert()
{
	if (!m_UTF8Value.empty())
	{
/*
		if (m_UTF8Value.length()>=4 && m_UTF8Value.substr(0,4)=="Live")
		{
			printf("%s\n",m_UTF8Value.c_str());

			for (std::string::size_type count=0;count<m_UTF8Value.length();count++)
				printf("%02x (%c)\n",(unsigned char)m_UTF8Value[count],m_UTF8Value[count]);
			printf("\n");
		}
*/

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

		std::stringstream NewCodeset;
		NewCodeset << Codeset << "//TRANSLIT//IGNORE";

		iconv_t Convert=iconv_open(NewCodeset.str().c_str(),"UTF-8");
		if ((iconv_t)-1!=Convert)
		{
			if ((size_t)-1!=iconv(Convert,&InBuff,&InLeft,&OutBuff,&OutLeft))
			{
				if (OutLeft>=sizeof(char))
				    *OutBuff='\0';

				m_DisplayValue=Out;
			}
			else
			{
				std::stringstream os;
				os << "iconv: "  << strerror(errno);
				CErrorLog::Log(os.str());
			}

			iconv_close(Convert);
		}
		else
		{
			std::stringstream os;
			os << "iconv_open: "  << strerror(errno);
			CErrorLog::Log(os.str());
		}

		if (In)
			delete[] In;

		if (Out)
			delete[] Out;

		if (m_DisplayValue.empty())
		{
			char *out=0;
			size_t out_length=0;
			m_DisplayValue=m_UTF8Value;

			if (0==unac_string("UTF-8",m_DisplayValue.c_str(),m_DisplayValue.length(),&out,&out_length))
				m_DisplayValue=out;
			else
				perror("unac_string");

			if (out)
				free(out);
		}
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

CUTF8Tag CUTF8Tag::operator+(const CUTF8Tag &Other)
{
	return m_UTF8Value + Other.m_UTF8Value;
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

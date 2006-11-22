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

#include "FileNameBuilder.h"

CFileNameBuilder::CFileNameBuilder(const tTagMap& Tags, const std::string& BasePath, const std::string& SingleDiskFileName, const std::string& MultiDiskFileName)
:	m_Tags(Tags),
	m_BasePath(BasePath),
	m_SingleDiskFileName(SingleDiskFileName),
	m_MultiDiskFileName(MultiDiskFileName)
{
	BuildPath();
}
	
std::string CFileNameBuilder::FileName() const
{
	return m_FileName;
}

void CFileNameBuilder::BuildPath()
{
	std::string Template;
	
	if (m_Tags[CTagName("DISCNUMBER")].empty())
		Template=m_SingleDiskFileName;
	else
		Template=m_MultiDiskFileName;
		
	m_FileName=m_BasePath+"/"+Template;
	
	ReplaceString("%A","ARTIST");
	ReplaceString("%S","ARTISTSORT");
	ReplaceString("%T","ALBUM");
	ReplaceString("%D","DISCNUMBER");
	ReplaceString("%Y","YEAR");
	ReplaceString("%G","GENRE");
}

void CFileNameBuilder::ReplaceString(const std::string& Search, const std::string& ReplaceTag)
{
	std::string Replace="NO"+ReplaceTag;
	
	tTagMap::const_iterator ThisTag=m_Tags.find(CTagName(ReplaceTag));
	if (m_Tags.end()!=ThisTag)
	{
		std::string Value=(*ThisTag).second;
		if (!Value.empty())
			Replace=FixString(Value);
	}
	
	std::string::size_type SearchPos=m_FileName.find(Search);
	while(std::string::npos!=SearchPos)
	{
		m_FileName=m_FileName.substr(0,SearchPos)+Replace+m_FileName.substr(SearchPos+Search.length());
		SearchPos=m_FileName.find(Search);
	}
}

std::string CFileNameBuilder::FixString(const std::string& String) const
{
	std::string Fixed=String;
	std::map<unsigned char,char> ReplaceChars;
		
	//0x20 is space		
	ReplaceChars[0x21]='-';
	ReplaceChars[0x22]='-';
	ReplaceChars[0x23]='-';
	ReplaceChars[0x24]='-';
	ReplaceChars[0x25]='-';
	ReplaceChars[0x26]='-';
	ReplaceChars[0x27]='-';
	ReplaceChars[0x28]='(';
	ReplaceChars[0x29]=')';
	ReplaceChars[0x2a]='-';
	ReplaceChars[0x2b]='+';
	ReplaceChars[0x2c]='-';
	ReplaceChars[0x2d]='-';
	//0x2e is .
	ReplaceChars[0x2f]='-';
	//Numbers 0-9
	ReplaceChars[0x3a]='-';
	ReplaceChars[0x3b]='-';
	ReplaceChars[0x3c]='-';
	//0x3d is =
	ReplaceChars[0x3e]='-';
	ReplaceChars[0x3f]='-';
	ReplaceChars[0x40]='-';
	//A-Z
	ReplaceChars[0x5b]='-';
	ReplaceChars[0x5c]='-';
	ReplaceChars[0x5d]='-';
	ReplaceChars[0x5e]='-';
	ReplaceChars[0x5f]='-';
	ReplaceChars[0x60]='-';
	//a-z
	ReplaceChars[0x7b]='-';
	ReplaceChars[0x7c]='-';
	ReplaceChars[0x7d]='-';
	ReplaceChars[0x7e]='-';
	ReplaceChars[0x7f]='-';
	ReplaceChars[0x80]='-';
	ReplaceChars[0x81]='-';
	ReplaceChars[0x82]='-';
	ReplaceChars[0x83]='f';
	ReplaceChars[0x84]='-';
	ReplaceChars[0x85]='-';
	ReplaceChars[0x86]='-';
	ReplaceChars[0x87]='-';
	ReplaceChars[0x88]='-';
	ReplaceChars[0x89]='-';
	ReplaceChars[0x8a]='S';
	ReplaceChars[0x8b]='-';
	ReplaceChars[0x8c]='-';
	ReplaceChars[0x8d]='-';
	ReplaceChars[0x8e]='Z';
	ReplaceChars[0x8f]='-';
	ReplaceChars[0x90]='-';
	ReplaceChars[0x91]='-';
	ReplaceChars[0x92]='-';
	ReplaceChars[0x93]='-';
	ReplaceChars[0x94]='-';
	ReplaceChars[0x95]='-';
	ReplaceChars[0x96]='-';
	ReplaceChars[0x97]='-';
	ReplaceChars[0x98]='-';
	ReplaceChars[0x99]='-';
	ReplaceChars[0x9a]='s';
	ReplaceChars[0x9b]='-';
	ReplaceChars[0x9c]='-';
	ReplaceChars[0x9d]='-';
	ReplaceChars[0x9e]='z';
	ReplaceChars[0x9f]='Y';
	ReplaceChars[0xa0]='-';
	ReplaceChars[0xa1]='i';
	ReplaceChars[0xa2]='c';
	ReplaceChars[0xa3]='-';
	ReplaceChars[0xa4]='-';
	ReplaceChars[0xa5]='Y';
	ReplaceChars[0xa6]='-';
	ReplaceChars[0xa7]='S';
	ReplaceChars[0xa8]='-';
	ReplaceChars[0xa9]='C';
	ReplaceChars[0xaa]='-';
	ReplaceChars[0xab]='-';
	ReplaceChars[0xac]='-';
	ReplaceChars[0xad]='-';
	ReplaceChars[0xae]='-';
	ReplaceChars[0xaf]='-';
	ReplaceChars[0xb0]='-';
	ReplaceChars[0xb1]='-';
	ReplaceChars[0xb2]='-';
	ReplaceChars[0xb3]='-';
	ReplaceChars[0xb4]='-';
	ReplaceChars[0xb5]='u';
	ReplaceChars[0xb6]='-';
	ReplaceChars[0xb7]='-';
	ReplaceChars[0xb8]='-';
	ReplaceChars[0xb9]='-';
	ReplaceChars[0xba]='-';
	ReplaceChars[0xbb]='-';
	ReplaceChars[0xbc]='-';
	ReplaceChars[0xbd]='-';
	ReplaceChars[0xbe]='-';
	ReplaceChars[0xbf]='-';
	ReplaceChars[0xc0]='A';
	ReplaceChars[0xc1]='A';
	ReplaceChars[0xc2]='A';
	ReplaceChars[0xc3]='A';
	ReplaceChars[0xc4]='A';
	ReplaceChars[0xc5]='A';
	ReplaceChars[0xc6]='-';
	ReplaceChars[0xc7]='C';
	ReplaceChars[0xc8]='E';
	ReplaceChars[0xc9]='E';
	ReplaceChars[0xca]='E';
	ReplaceChars[0xcb]='E';
	ReplaceChars[0xcc]='I';
	ReplaceChars[0xcd]='I';
	ReplaceChars[0xce]='I';
	ReplaceChars[0xcf]='I';
	ReplaceChars[0xd0]='D';
	ReplaceChars[0xd1]='N';
	ReplaceChars[0xd2]='O';
	ReplaceChars[0xd3]='O';
	ReplaceChars[0xd4]='O';
	ReplaceChars[0xd5]='O';
	ReplaceChars[0xd6]='O';
	ReplaceChars[0xd7]='x';
	ReplaceChars[0xd8]='O';
	ReplaceChars[0xd9]='U';
	ReplaceChars[0xda]='U';
	ReplaceChars[0xdb]='U';
	ReplaceChars[0xdc]='U';
	ReplaceChars[0xdd]='Y';
	ReplaceChars[0xde]='-';
	ReplaceChars[0xdf]='B';
	ReplaceChars[0xe0]='a';
	ReplaceChars[0xe1]='a';
	ReplaceChars[0xe2]='a';
	ReplaceChars[0xe3]='a';
	ReplaceChars[0xe4]='a';
	ReplaceChars[0xe5]='a';
	ReplaceChars[0xe6]='a';
	ReplaceChars[0xe7]='c';
	ReplaceChars[0xe8]='e';
	ReplaceChars[0xe9]='e';
	ReplaceChars[0xea]='e';
	ReplaceChars[0xeb]='e';
	ReplaceChars[0xec]='i';
	ReplaceChars[0xed]='i';
	ReplaceChars[0xee]='i';
	ReplaceChars[0xef]='i';
	ReplaceChars[0xf0]='o';
	ReplaceChars[0xf1]='n';
	ReplaceChars[0xf2]='o';
	ReplaceChars[0xf3]='o';
	ReplaceChars[0xf4]='o';
	ReplaceChars[0xf5]='o';
	ReplaceChars[0xf6]='o';
	ReplaceChars[0xf7]='-';
	ReplaceChars[0xf8]='o';
	ReplaceChars[0xf9]='u';
	ReplaceChars[0xfa]='u';
	ReplaceChars[0xfb]='u';
	ReplaceChars[0xfc]='u';
	ReplaceChars[0xfd]='y';
	ReplaceChars[0xfe]='p';
	ReplaceChars[0xff]='y';
	
	for (std::string::size_type count=0;count<Fixed.length();count++)
	{
		std::map<unsigned char,char>::const_iterator BadChar=ReplaceChars.find(Fixed[count]);
		if (ReplaceChars.end()!=BadChar)
			Fixed[count]=(*BadChar).second;			
	}
	
	return Fixed;
}

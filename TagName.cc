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

#include "TagName.h"

#include <sstream>

CTagName::CTagName(const std::string& Name, int Number)
:	m_Name(Name),
	m_Number(Number)
{
}

CTagName::CTagName(const std::string& Name)
:	m_Name(Name),
	m_Number(-1)
{
	std::string::size_type OpenPos=Name.find("[");
	
	if (std::string::npos!=OpenPos)
	{
		std::string::size_type ClosePos=Name.find("]",OpenPos);
		if (std::string::npos!=ClosePos)
		{
			std::string NumberStr=Name.substr(OpenPos+1,ClosePos-OpenPos-1);
			m_Number=atoi(NumberStr.c_str());
			m_Name=Name.substr(0,OpenPos);
		}
	}
}

bool CTagName::operator <(const CTagName& Other) const
{
	//return String()<Other.String();
		
	bool RetVal=false;

	if (!SpecialTag() && Other.SpecialTag())
		RetVal=true;
	else if (SpecialTag()==Other.SpecialTag() && m_Number<Other.m_Number)
		RetVal=true;
	else if (SpecialTag()==Other.SpecialTag() && m_Number==Other.m_Number && m_Name=="TRACKNUMBER" && Other.m_Name!="TRACKNUMBER")
		RetVal=true;
	else if (SpecialTag()==Other.SpecialTag() && m_Number==Other.m_Number && m_Name!="TRACKNUMBER" && Other.m_Name=="TRACKNUMBER")
		RetVal=false;
	else if (SpecialTag()==Other.SpecialTag() && m_Number==Other.m_Number && m_Name!="TRACKNUMBER" && Other.m_Name!="TRACKNUMBER" && m_Name<Other.m_Name)
		RetVal=true;
	
	return RetVal;
}

bool CTagName::operator >(const CTagName& Other) const
{
	bool RetVal=!(*this<Other) && !(*this==Other);
	
	return RetVal;
}

bool CTagName::operator ==(const CTagName& Other) const
{
	bool RetVal=(m_Name==Other.m_Name && m_Number==Other.m_Number);
	
	return RetVal;
}

std::string CTagName::Name() const
{
	return m_Name;
}

int CTagName::Number() const
{
	return m_Number;
}

bool CTagName::SpecialTag() const
{
	bool RetVal=(std::string::npos!=m_Name.find("REPLAYGAIN") ||
								std::string::npos!=m_Name.find("DISCID"));
		
	return RetVal;
}

std::string CTagName::String() const
{
	std::stringstream os;
	
	if (m_Number==-1)
		os << m_Name;
	else
		os << m_Name << "[" << m_Number <<"]";
		
	return os.str();
}

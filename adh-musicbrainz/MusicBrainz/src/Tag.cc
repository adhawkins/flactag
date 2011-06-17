/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
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

#include "musicbrainz4/Tag.h"

#include <sstream>

MusicBrainz4::CTag::CTag(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Tag node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("count"))
		{
			std::stringstream os;
			os << Node.getAttribute("type");
			os >> m_Count;
		}

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("name"==NodeName)
			{
				m_Name=NodeValue;
			}
			else
			{
				std::cerr << "Unrecognised tag node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CTag::CTag(const CTag& Other)
{
	*this=Other;
}

MusicBrainz4::CTag& MusicBrainz4::CTag::operator =(const CTag& Other)
{
	if (this!=&Other)
	{
		m_Count=Other.m_Count;
		m_Name=Other.m_Name;
	}

	return *this;
}

int MusicBrainz4::CTag::Count() const
{
	return m_Count;
}

std::string MusicBrainz4::CTag::Name() const
{
	return m_Name;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CTag& Tag)
{
	os << "Tag:" << std::endl;

	os << "\tCount: " << Tag.Count() << std::endl;
	os << "\tName:  " << Tag.Name() << std::endl;

	return os;
}

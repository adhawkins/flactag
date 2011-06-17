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

#include "musicbrainz4/FreeDBDisc.h"

#include "musicbrainz4/NoneMBTrack.h"

MusicBrainz4::CFreeDBDisc::CFreeDBDisc(const XMLNode& Node)
:	m_NoneMBTrackList(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "FreeDBDisc node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("id"))
			m_ID=Node.getAttribute("id");

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("title"==NodeName)
			{
				m_Title=NodeValue;
			}
			else if ("artist"==NodeName)
			{
				m_Artist=NodeValue;
			}
			else if ("category"==NodeName)
			{
				m_Category=NodeValue;
			}
			else if ("year"==NodeName)
			{
				m_Year=NodeValue;
			}
			else if ("nonmb-track-list"==NodeName)
			{
				m_NoneMBTrackList=new CGenericList<CNoneMBTrack>(ChildNode,"track");
			}
			else
			{
				std::cerr << "Unrecognised cd stub node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CFreeDBDisc::CFreeDBDisc(const CFreeDBDisc& Other)
:	m_NoneMBTrackList(0)
{
	*this=Other;
}

MusicBrainz4::CFreeDBDisc& MusicBrainz4::CFreeDBDisc::operator =(const CFreeDBDisc& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_ID=Other.m_ID;
		m_Title=Other.m_Title;
		m_Artist=Other.m_Artist;
		m_Category=Other.m_Category;
		m_Year=Other.m_Year;

		if (Other.m_NoneMBTrackList)
			m_NoneMBTrackList=new CGenericList<CNoneMBTrack>(*Other.m_NoneMBTrackList);
	}

	return *this;
}

MusicBrainz4::CFreeDBDisc::~CFreeDBDisc()
{
	Cleanup();
}

void MusicBrainz4::CFreeDBDisc::Cleanup()
{
	delete m_NoneMBTrackList;
	m_NoneMBTrackList=0;
}

std::string MusicBrainz4::CFreeDBDisc::ID() const
{
	return m_ID;
}

std::string MusicBrainz4::CFreeDBDisc::Title() const
{
	return m_Title;
}

std::string MusicBrainz4::CFreeDBDisc::Artist() const
{
	return m_Artist;
}

std::string MusicBrainz4::CFreeDBDisc::Category() const
{
	return m_Category;
}

std::string MusicBrainz4::CFreeDBDisc::Year() const
{
	return m_Year;
}

MusicBrainz4::CGenericList<MusicBrainz4::CNoneMBTrack> *MusicBrainz4::CFreeDBDisc::NoneMBTrackList() const
{
	return m_NoneMBTrackList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CFreeDBDisc& FreeDBDisc)
{
	os << "FreeDBDisc:" << std::endl;

	os << "\tID:       " << FreeDBDisc.ID() << std::endl;
	os << "\tTitle:    " << FreeDBDisc.Title() << std::endl;
	os << "\tArtist:   " << FreeDBDisc.Artist() << std::endl;
	os << "\tCategory: " << FreeDBDisc.Category() << std::endl;
	os << "\tYear:     " << FreeDBDisc.Year() << std::endl;

	if (FreeDBDisc.NoneMBTrackList())
		os << *FreeDBDisc.NoneMBTrackList() << std::endl;

	return os;
}

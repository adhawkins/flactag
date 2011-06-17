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

#include "musicbrainz4/Work.h"

#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/Alias.h"
#include "musicbrainz4/Relation.h"
#include "musicbrainz4/Tag.h"
#include "musicbrainz4/UserTag.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/UserRating.h"

MusicBrainz4::CWork::CWork(const XMLNode& Node)
:	m_ArtistCredit(0),
	m_AliasList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Work node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("id"))
			m_ID=Node.getAttribute("id");

		if (Node.isAttributeSet("type"))
			m_Type=Node.getAttribute("type");

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
			else if ("artist-credit"==NodeName)
			{
				m_ArtistCredit=new CArtistCredit(ChildNode);
			}
			else if ("iswc"==NodeName)
			{
				m_ISWC=NodeValue;
			}
			else if ("disambiguation"==NodeName)
			{
				m_Disambiguation=NodeValue;
			}
			else if ("alias-list"==NodeName)
			{
				m_AliasList=new CGenericList<CAlias>(ChildNode,"alias");
			}
			else if ("relation-list"==NodeName)
			{
				m_RelationList=new CGenericList<CRelation>(ChildNode,"relation");
			}
			else if ("tag-list"==NodeName)
			{
				m_TagList=new CGenericList<CTag>(ChildNode,"tag");
			}
			else if ("user-tag-list"==NodeName)
			{
				m_UserTagList=new CGenericList<CUserTag>(ChildNode,"user-tag");
			}
			else if ("rating"==NodeName)
			{
				m_Rating=new CRating(ChildNode);
			}
			else if ("user-rating"==NodeName)
			{
				m_UserRating=new CUserRating(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised work node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CWork::CWork(const CWork& Other)
:	m_ArtistCredit(0),
	m_AliasList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	*this=Other;
}

MusicBrainz4::CWork& MusicBrainz4::CWork::operator =(const CWork& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_ID=Other.m_ID;
		m_Type=Other.m_Type;
		m_Title=Other.m_Title;

		if (Other.m_ArtistCredit)
			m_ArtistCredit=new CArtistCredit(*Other.m_ArtistCredit);

		m_ISWC=Other.m_ISWC;
		m_Disambiguation=Other.m_Disambiguation;

		if (Other.m_AliasList)
			m_AliasList=new CGenericList<CAlias>(*Other.m_AliasList);

		if (Other.m_RelationList)
			m_RelationList=new CGenericList<CRelation>(*Other.m_RelationList);

		if (Other.m_TagList)
			m_TagList=new CGenericList<CTag>(*Other.m_TagList);

		if (Other.m_UserTagList)
			m_UserTagList=new CGenericList<CUserTag>(*Other.m_UserTagList);

		if (Other.m_Rating)
			m_Rating=new CRating(*Other.m_Rating);

		if (Other.m_UserRating)
			m_UserRating=new CUserRating(*Other.m_UserRating);
	}

	return *this;
}

MusicBrainz4::CWork::~CWork()
{
	Cleanup();
}

void MusicBrainz4::CWork::Cleanup()
{
	delete m_ArtistCredit;
	m_ArtistCredit=0;

	delete m_AliasList;
	m_AliasList=0;

	delete m_RelationList;
	m_RelationList=0;

	delete m_TagList;
	m_TagList=0;

	delete m_UserTagList;
	m_UserTagList=0;

	delete m_Rating;
	m_Rating=0;

	delete m_UserRating;
	m_UserRating=0;
}

std::string MusicBrainz4::CWork::ID() const
{
	return m_ID;
}

std::string MusicBrainz4::CWork::Type() const
{
	return m_Type;
}

std::string MusicBrainz4::CWork::Title() const
{
	return m_Title;
}

MusicBrainz4::CArtistCredit *MusicBrainz4::CWork::ArtistCredit() const
{
	return m_ArtistCredit;
}

std::string MusicBrainz4::CWork::ISWC() const
{
	return m_ISWC;
}

std::string MusicBrainz4::CWork::Disambiguation() const
{
	return m_Disambiguation;
}

MusicBrainz4::CGenericList<MusicBrainz4::CAlias> *MusicBrainz4::CWork::AliasList() const
{
	return m_AliasList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelation> *MusicBrainz4::CWork::RelationList() const
{
	return m_RelationList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CTag> *MusicBrainz4::CWork::TagList() const
{
	return m_TagList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CUserTag> *MusicBrainz4::CWork::UserTagList() const
{
	return m_UserTagList;
}

MusicBrainz4::CRating *MusicBrainz4::CWork::Rating() const
{
	return m_Rating;
}

MusicBrainz4::CUserRating *MusicBrainz4::CWork::UserRating() const
{
	return m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CWork& Work)
{
	os << "Work:" << std::endl;

	os << "\tID:             " << Work.ID() << std::endl;
	os << "\tWork:           " << Work.Type() << std::endl;
	os << "\tTitle:          " << Work.Title() << std::endl;
	if (Work.ArtistCredit())
		os << Work.ArtistCredit() << std::endl;
	os << "\tISWC:           " << Work.ISWC() << std::endl;

	os << "\tDisambiguation: " << Work.Disambiguation() << std::endl;
	if (Work.AliasList())
		os << Work.AliasList() << std::endl;

	if (Work.RelationList())
		os << Work.RelationList() << std::endl;

	if (Work.TagList())
		os << Work.TagList() << std::endl;

	if (Work.UserTagList())
		os << Work.UserTagList() << std::endl;

	if (Work.Rating())
		os << Work.Rating() << std::endl;

	if (Work.UserRating())
		os << Work.UserRating() << std::endl;

	return os;
}


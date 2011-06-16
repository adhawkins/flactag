#ifndef _MUSICBRAINZ4_GENERIC_LIST_H
#define _MUSICBRAINZ4_GENERIC_LIST_H

#include <list>
#include <iostream>
#include <string>

#include "xmlParser.h"

namespace MusicBrainz4
{
	template <class T>
	class CGenericList
	{
	public:
		CGenericList(const XMLNode& Node=XMLNode::emptyNode(), const std::string& SubNodeName="")
		:	m_SubNodeName(SubNodeName)
		{
			if (!Node.isEmpty())
			{
				//std::cout << m_SubNodeName << " node: " << std::endl << Node.createXMLString(true) << std::endl;

				int nItems=Node.nChildNode(SubNodeName.c_str());

				for (int count=0;count<nItems;count++)
				{
					XMLNode ItemNode=Node.getChildNode(SubNodeName.c_str(),count);
					m_Items.push_back(T(ItemNode));
				}
			}
		}

		std::string SubNodeName() const { return m_SubNodeName; }
		std::list<T> Items() const { return m_Items; }

	private:
		std::string m_SubNodeName;
		std::list<T> m_Items;
	};
}

template <class T>
std::ostream& operator << (std::ostream& os, MusicBrainz4::CGenericList<T>& List)
{
	os << List.SubNodeName() << " list:" << std::endl;

	typedef std::list<T> TList;
	typedef typename TList::const_iterator TListConstIterator;

	TList Items=List.Items();
	TListConstIterator ThisItem=Items.begin();
	while (ThisItem!=Items.end())
	{
		os << *ThisItem << std::endl;

		++ThisItem;
	}

	return os;
}

#endif

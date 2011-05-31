#ifndef _MBADH_RELEASE_LIST_H
#define _MBADH_RELEASE_LIST_H

#include <vector>
#include <iostream>
#include <string>

#include "xmlParser/xmlParser.h"

namespace MusicBrainzADH
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
		std::vector<T> Items() const { return m_Items; }
			
	private:
		std::string m_SubNodeName;
		std::vector<T> m_Items;
	};
}

template <class T>
std::ostream& operator << (std::ostream& os, MusicBrainzADH::CGenericList<T>& List)
{
	os << List.SubNodeName() << " list:" << std::endl;

	typedef std::vector<T> TVector;
	typedef typename TVector::const_iterator TVectorConstIterator;
			
	TVector Items=List.Items();
	TVectorConstIterator ThisItem=Items.begin();
	while (ThisItem!=Items.end())
	{
		T Item=*ThisItem;
		os << Item << std::endl;
		
		++ThisItem;
	}
	
	return os;
}

#endif

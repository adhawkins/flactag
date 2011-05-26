#include "Artist.h"

CArtist::CArtist(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Artist node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		if (Node.isAttributeSet("id"))			
			m_ID=Node.getAttribute("id");
		
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
			else if ("sort-name"==NodeName)
			{
				m_SortName=NodeValue;
			}
			else if ("disambiguation"==NodeName)
			{
				m_Disambiguation=NodeValue;
			}
			else
			{
				std::cerr << "Unrecognised artist node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

std::string CArtist::ID() const
{
	return m_ID;
}

std::string CArtist::Name() const
{
	return m_Name;
}

std::string CArtist::SortName() const
{
	return m_SortName;
}

std::string CArtist::Disambiguation() const
{
	return m_Disambiguation;
}

std::ostream& operator << (std::ostream& os, const CArtist& Artist)
{
	os << "Artist:" << std::endl;
		
	os << "\tID:             " << Artist.m_ID << std::endl;
	os << "\tName:           " << Artist.m_Name << std::endl;
	os << "\tSort name:      " << Artist.m_SortName << std::endl;
	os << "\tDisambiguation: " << Artist.m_Disambiguation << std::endl;

	return os;
}
	

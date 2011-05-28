#include "Artist.h"

MusicBrainzADH::CArtist::CArtist(const XMLNode& Node)
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

std::string MusicBrainzADH::CArtist::ID() const
{
	return m_ID;
}

std::string MusicBrainzADH::CArtist::Name() const
{
	return m_Name;
}

std::string MusicBrainzADH::CArtist::SortName() const
{
	return m_SortName;
}

std::string MusicBrainzADH::CArtist::Disambiguation() const
{
	return m_Disambiguation;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CArtist& Artist)
{
	os << "Artist:" << std::endl;
		
	os << "\tID:             " << Artist.ID() << std::endl;
	os << "\tName:           " << Artist.Name() << std::endl;
	os << "\tSort name:      " << Artist.SortName() << std::endl;
	os << "\tDisambiguation: " << Artist.Disambiguation() << std::endl;

	return os;
}
	

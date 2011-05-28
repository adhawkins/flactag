#include "Label.h"

#include <iostream>

MusicBrainzADH::CLabel::CLabel(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Label node: " << std::endl << Node.createXMLString(true) << std::endl;
			
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
			else if ("label-code"==NodeName)
			{
				m_LabelCode=NodeValue;
			}
			else
			{
				std::cerr << "Unrecognised label node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

std::string MusicBrainzADH::CLabel::ID() const
{
	return m_ID;
}

std::string MusicBrainzADH::CLabel::Name() const
{
	return m_Name;
}

std::string MusicBrainzADH::CLabel::SortName() const
{
	return m_SortName;
}

std::string MusicBrainzADH::CLabel::LabelCode() const
{
	return m_LabelCode;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CLabel& Label)
{
	os << "Label:" << std::endl;
		
	os << "\tID:         " << Label.ID() << std::endl;
	os << "\tName:       " << Label.Name() << std::endl;
	os << "\tSort name:  " << Label.SortName() << std::endl;
	os << "\tLabel code: " << Label.LabelCode() << std::endl;
		
	return os;
}
	

#include "Label.h"

#include <iostream>

CLabel::CLabel(const XMLNode& Node)
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

std::string CLabel::ID() const
{
	return m_ID;
}

std::string CLabel::Name() const
{
	return m_Name;
}

std::string CLabel::SortName() const
{
	return m_SortName;
}

std::string CLabel::LabelCode() const
{
	return m_LabelCode;
}

std::ostream& operator << (std::ostream& os, const CLabel& Label)
{
	os << "Label:" << std::endl;
		
	os << "\tID:         " << Label.m_ID << std::endl;
	os << "\tName:       " << Label.m_Name << std::endl;
	os << "\tSort name:  " << Label.m_SortName << std::endl;
	os << "\tLabel code: " << Label.m_LabelCode << std::endl;
		
	return os;
}
	

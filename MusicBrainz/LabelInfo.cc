#include "LabelInfo.h"

CLabelInfo::CLabelInfo(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Label info node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();
			
			if ("catalog-number"==NodeName)
			{
				m_CatalogNumber=NodeValue;
			}
			else if ("label"==NodeName)
			{
				m_Label=CLabel(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised label info node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

std::string CLabelInfo::CatalogNumber() const
{
	return m_CatalogNumber;
}

CLabel CLabelInfo::Label() const
{
	return m_Label;
}

std::ostream& operator << (std::ostream& os, const CLabelInfo& LabelInfo)
{
	os << "Label info:" << std::endl;
		
	os << "\tCatalog number: " << LabelInfo.m_CatalogNumber << std::endl;
	os << LabelInfo.m_Label << std::endl;
		
	return os;
}
	

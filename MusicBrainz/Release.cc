#include "Release.h"

#include <iostream>

#include "xmlParser/xmlParser.h"

CRelease::CRelease(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		std::cout << "Release node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		m_ID=Node.getAttribute("id");
		
		std::cout << "ID is '" << m_ID << "'" << std::endl;
			
		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			
			//std::cout << "Node " << count << " is '" << ChildNode.getName() << "'" << std::endl;
		}
	}
}

std::string CRelease::ID() const
{
	return m_ID;
}

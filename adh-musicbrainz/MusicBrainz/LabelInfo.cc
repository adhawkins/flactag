#include "LabelInfo.h"

#include "Label.h"

MusicBrainzADH::CLabelInfo::CLabelInfo(const XMLNode& Node)
:	m_Label(0)
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
				m_Label=new CLabel(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised label info node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainzADH::CLabelInfo::CLabelInfo(const CLabelInfo& Other)
:	m_Label(0)
{
	*this=Other;
}

MusicBrainzADH::CLabelInfo& MusicBrainzADH::CLabelInfo::operator =(const CLabelInfo& Other)
{
	if (this!=&Other)
	{
		Cleanup();
		
		m_CatalogNumber=Other.m_CatalogNumber;
		
		if (Other.m_Label)
			m_Label=new CLabel(*Other.m_Label);
	}
	
	return *this;
}

MusicBrainzADH::CLabelInfo::~CLabelInfo()
{
	Cleanup();
}

void MusicBrainzADH::CLabelInfo::Cleanup()
{
	delete m_Label;
	m_Label=0;
}

std::string MusicBrainzADH::CLabelInfo::CatalogNumber() const
{
	return m_CatalogNumber;
}

MusicBrainzADH::CLabel *MusicBrainzADH::CLabelInfo::Label() const
{
	return m_Label;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CLabelInfo& LabelInfo)
{
	os << "Label info:" << std::endl;
		
	os << "\tCatalog number: " << LabelInfo.CatalogNumber() << std::endl;

	if (LabelInfo.Label())
		os << *LabelInfo.Label() << std::endl;
		
	return os;
}
	

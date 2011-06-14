#include "musicbrainz4/LabelInfo.h"

#include "musicbrainz4/Label.h"

MusicBrainz4::CLabelInfo::CLabelInfo(const XMLNode& Node)
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

MusicBrainz4::CLabelInfo::CLabelInfo(const CLabelInfo& Other)
:	m_Label(0)
{
	*this=Other;
}

MusicBrainz4::CLabelInfo& MusicBrainz4::CLabelInfo::operator =(const CLabelInfo& Other)
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

MusicBrainz4::CLabelInfo::~CLabelInfo()
{
	Cleanup();
}

void MusicBrainz4::CLabelInfo::Cleanup()
{
	delete m_Label;
	m_Label=0;
}

std::string MusicBrainz4::CLabelInfo::CatalogNumber() const
{
	return m_CatalogNumber;
}

MusicBrainz4::CLabel *MusicBrainz4::CLabelInfo::Label() const
{
	return m_Label;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CLabelInfo& LabelInfo)
{
	os << "Label info:" << std::endl;

	os << "\tCatalog number: " << LabelInfo.CatalogNumber() << std::endl;

	if (LabelInfo.Label())
		os << *LabelInfo.Label() << std::endl;

	return os;
}


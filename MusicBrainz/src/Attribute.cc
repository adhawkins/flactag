#include "musicbrainz4/Attribute.h"

MusicBrainz4::CAttribute::CAttribute(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Attribute node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.getText())
			m_Text=Node.getText();
	}
}

MusicBrainz4::CAttribute::CAttribute(const CAttribute& Other)
{
	*this=Other;
}

MusicBrainz4::CAttribute& MusicBrainz4::CAttribute::operator =(const CAttribute& Other)
{
	if (this!=&Other)
	{
		m_Text=Other.m_Text;
	}

	return *this;
}

std::string MusicBrainz4::CAttribute::Text() const
{
	return m_Text;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CAttribute& Attribute)
{
	os << "Attribute:" << std::endl;

	os << "\tText: " << Attribute.Text() << std::endl;

	return os;
}



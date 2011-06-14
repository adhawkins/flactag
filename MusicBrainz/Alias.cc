#include "Alias.h"

MusicBrainz4::CAlias::CAlias(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Relation node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("type"))
			m_Type=Node.getAttribute("type");

		if (Node.isAttributeSet("script"))
			m_Script=Node.getAttribute("script");

		if (Node.getText())
			m_Text=Node.getText();
	}
}

MusicBrainz4::CAlias::CAlias(const CAlias& Other)
{
	*this=Other;
}

MusicBrainz4::CAlias& MusicBrainz4::CAlias::operator =(const CAlias& Other)
{
	if (this!=&Other)
	{
		m_Type=Other.m_Type;
		m_Script=Other.m_Type;
		m_Text=Other.m_Text;
	}

	return *this;
}

std::string MusicBrainz4::CAlias::Type() const
{
	return m_Type;
}

std::string MusicBrainz4::CAlias::Script() const
{
	return m_Script;
}

std::string MusicBrainz4::CAlias::Text() const
{
	return m_Text;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CAlias& Alias)
{
	os << "Alias:" << std::endl;

	os << "\tType:   " << Alias.Type() << std::endl;
	os << "\tScript: " << Alias.Script() << std::endl;
	os << "\tText:   " << Alias.Text() << std::endl;

	return os;
}

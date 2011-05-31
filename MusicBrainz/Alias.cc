#include "Alias.h"

MusicBrainzADH::CAlias::CAlias(const XMLNode& Node)
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

MusicBrainzADH::CAlias::CAlias(const CAlias& Other)
{
	*this=Other;
}

MusicBrainzADH::CAlias& MusicBrainzADH::CAlias::operator =(const CAlias& Other)
{
	if (this!=&Other)
	{
		m_Type=Other.m_Type;
		m_Script=Other.m_Type;
		m_Text=Other.m_Text;
	}
	
	return *this;
}
	
std::string MusicBrainzADH::CAlias::Type() const
{
	return m_Type;
}

std::string MusicBrainzADH::CAlias::Script() const
{
	return m_Script;
}

std::string MusicBrainzADH::CAlias::Text() const
{
	return m_Text;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CAlias& Alias)
{
	os << "Alias:" << std::endl;
		
	os << "\tType:   " << Alias.Type() << std::endl;
	os << "\tScript: " << Alias.Script() << std::endl;
	os << "\tText:   " << Alias.Text() << std::endl;
		
	return os;
}

#include "Attribute.h"

MusicBrainzADH::CAttribute::CAttribute(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Attribute node: " << std::endl << Node.createXMLString(true) << std::endl;
		
		if (Node.getText())
			m_Text=Node.getText();
	}	
}

MusicBrainzADH::CAttribute::CAttribute(const CAttribute& Other)
{
	*this=Other;
}

MusicBrainzADH::CAttribute& MusicBrainzADH::CAttribute::operator =(const CAttribute& Other)
{
	if (this!=&Other)
	{
		m_Text=Other.m_Text;
	}
	
	return *this;
}

std::string MusicBrainzADH::CAttribute::Text() const
{
	return m_Text;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CAttribute& Attribute)
{
	os << "Attribute:" << std::endl;
		
	os << "\tText: " << Attribute.Text() << std::endl;
		
	return os;
}



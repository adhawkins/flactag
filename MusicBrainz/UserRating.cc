#include "UserRating.h"

#include <sstream>

MusicBrainzADH::CUserRating::CUserRating(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "User rating node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		if (Node.getText())
		{
			std::stringstream os;
			os << Node.getText();		
			os >> m_UserRating;
		}
	}	
}

MusicBrainzADH::CUserRating::CUserRating(const CUserRating& Other)
{
	*this=Other;
}

MusicBrainzADH::CUserRating& MusicBrainzADH::CUserRating::operator =(const CUserRating& Other)
{
	if (this!=&Other)
	{
		m_UserRating=Other.m_UserRating;
	}
	
	return *this;
}

int MusicBrainzADH::CUserRating::UserRating() const
{
	return m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CUserRating& UserRating)
{
	os << "User rating:" << std::endl;
		
	os << "\tRating: " << UserRating.UserRating() << std::endl;

	return os;
}

#include "musicbrainz4/UserRating.h"

#include <sstream>

MusicBrainz4::CUserRating::CUserRating(const XMLNode& Node)
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

MusicBrainz4::CUserRating::CUserRating(const CUserRating& Other)
{
	*this=Other;
}

MusicBrainz4::CUserRating& MusicBrainz4::CUserRating::operator =(const CUserRating& Other)
{
	if (this!=&Other)
	{
		m_UserRating=Other.m_UserRating;
	}

	return *this;
}

int MusicBrainz4::CUserRating::UserRating() const
{
	return m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CUserRating& UserRating)
{
	os << "User rating:" << std::endl;

	os << "\tRating: " << UserRating.UserRating() << std::endl;

	return os;
}

#ifndef _USER_RATING_H
#define _USER_RATING_H

#include <iostream>

#include "xmlParser/xmlParser.h"

namespace MusicBrainzADH
{
	class CUserRating
	{
	public:
		CUserRating(const XMLNode& Node);
		CUserRating(const CUserRating& Other);
		CUserRating& operator =(const CUserRating& Other);

		int UserRating() const;
		
	private:
		int m_UserRating;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CUserRating& UserRating);

#endif

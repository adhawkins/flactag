#ifndef _RATING_H
#define _RATING_H

#include <iostream>

#include "xmlParser/xmlParser.h"

namespace MusicBrainzADH
{
	class CRating
	{
	public:
		CRating(const XMLNode& Node=XMLNode::emptyNode());
		CRating(const CRating& Other);
		CRating& operator =(const CRating& Other);

		int VotesCount() const;
		double Rating() const;
	
	private:
		int m_VotesCount;
		double m_Rating;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CRating& Rating);

#endif

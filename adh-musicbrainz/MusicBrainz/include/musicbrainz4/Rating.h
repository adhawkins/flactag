#ifndef _MUSICBRAINZ4_RATING_H
#define _MUSICBRAINZ4_RATING_H

#include <iostream>

#include "xmlParser.h"

namespace MusicBrainz4
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

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRating& Rating);

#endif

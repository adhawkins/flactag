#include "Rating.h"

#include <sstream>

MusicBrainz4::CRating::CRating(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Rating node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("votes-count"))
		{
			std::stringstream os;
			os << Node.getAttribute("votes-count");
			os >> m_VotesCount;
		}

		if (Node.getText())
		{
			std::stringstream os;
			os << Node.getText();
			os >> m_Rating;
		}
	}
}

MusicBrainz4::CRating::CRating(const CRating& Other)
{
	*this=Other;
}

MusicBrainz4::CRating& MusicBrainz4::CRating::operator =(const CRating& Other)
{
	if (this!=&Other)
	{
		m_VotesCount=Other.m_VotesCount;
		m_Rating=Other.m_Rating;
	}

	return *this;
}

int MusicBrainz4::CRating::VotesCount() const
{
	return m_VotesCount;
}

double MusicBrainz4::CRating::Rating() const
{
	return m_Rating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRating& Rating)
{
	os << "Rating:" << std::endl;

	os << "\tVotes count: " << Rating.VotesCount() << std::endl;
	os << "\tRating:      " << Rating.Rating() << std::endl;

	return os;
}

#include "Rating.h"

#include <sstream>

MusicBrainzADH::CRating::CRating(const XMLNode& Node)
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

MusicBrainzADH::CRating::CRating(const CRating& Other)
{
	*this=Other;
}

MusicBrainzADH::CRating& MusicBrainzADH::CRating::operator =(const CRating& Other)
{
	if (this!=&Other)
	{
		m_VotesCount=Other.m_VotesCount;
		m_Rating=Other.m_Rating;
	}
	
	return *this;
}

int MusicBrainzADH::CRating::VotesCount() const
{
	return m_VotesCount;
}
	
double MusicBrainzADH::CRating::Rating() const
{
	return m_Rating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CRating& Rating)
{
	os << "Rating:" << std::endl;
		
	os << "\tVotes count: " << Rating.VotesCount() << std::endl;
	os << "\tRating:      " << Rating.Rating() << std::endl;
		
	return os;
}

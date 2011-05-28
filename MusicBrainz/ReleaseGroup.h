#ifndef _MBADH_RELEASE_GROUP_H
#define _MBADH_RELEASE_GROUP_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "ArtistCredit.h"

namespace MusicBrainzADH
{
	class CReleaseGroup
	{
	public:
		CReleaseGroup(const XMLNode& Node=XMLNode::emptyNode());
	
		std::string ID() const;
		std::string Title() const;
		CArtistCredit ArtistCredit() const;
	
	private:
		std::string m_ID;
		std::string m_Title;
		CArtistCredit m_ArtistCredit;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CReleaseGroup& ReleaseGroup);

#endif

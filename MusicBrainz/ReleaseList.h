#ifndef _MBADH_RELEASE_LIST_H
#define _MBADH_RELEASE_LIST_H

#include <vector>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "Release.h"

namespace MusicBrainzADH
{
	class CReleaseList
	{
	public:
		CReleaseList(const XMLNode& Node=XMLNode::emptyNode());
		
		std::vector<MusicBrainzADH::CRelease> Releases() const;
		
	private:
		std::vector<MusicBrainzADH::CRelease> m_Releases;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CReleaseList& ReleaseList);

#endif
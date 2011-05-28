#ifndef _MBADH_MEDIUM_LIST_H
#define _MBADH_MEDIUM_LIST_H

#include <vector>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "Medium.h"

namespace MusicBrainzADH
{
	class CMediumList
	{
	public:
		CMediumList(const XMLNode& Node=XMLNode::emptyNode());
		
		std::vector<CMedium> Media() const;
	
	private:
		std::vector<CMedium> m_Media;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CMediumList& MediumList);

#endif

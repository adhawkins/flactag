#ifndef _MBADH_DISC_LIST_H
#define _MBADH_DISC_LIST_H

#include <vector>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "Disc.h"

namespace MusicBrainzADH
{
	class CDiscList
	{
	public:
		CDiscList(const XMLNode& Node=XMLNode::emptyNode());
		
		std::vector<CDisc> Discs() const;
	
		bool ContainsDiscID(const std::string& DiscID) const;
				
	private:
		std::vector<CDisc> m_Discs;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CDiscList& DiscList);

#endif

#ifndef _MBADH_DISC_H
#define _MBADH_DISC_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

namespace MusicBrainzADH
{
	class CDisc
	{
	public:
		CDisc(const XMLNode& Node=XMLNode::emptyNode());
	
		std::string ID() const;
		std::string Sectors() const;
			
	private:
		std::string m_ID;
		std::string m_Sectors;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CDisc& Disc);

#endif

#ifndef _MBADH_DISC_H
#define _MBADH_DISC_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "Lifespan.h"
#include "GenericList.h"

namespace MusicBrainzADH
{
	class CRelease;
	
	class CDisc
	{
	public:
		CDisc(const XMLNode& Node=XMLNode::emptyNode());
		CDisc(const CDisc& Other);
		CDisc& operator =(const CDisc& Other);
		~CDisc();
	
		std::string ID() const;
		std::string Sectors() const;
		CGenericList<CRelease> *ReleaseList() const;
			
	private:
		void Cleanup();
		
		std::string m_ID;
		std::string m_Sectors;
		CGenericList<CRelease> *m_ReleaseList;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CDisc& Disc);

#endif

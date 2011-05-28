#ifndef _MBADH_LABEL_INFO_H
#define _MBADH_LABEL_INFO_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "Label.h"

namespace MusicBrainzADH
{
	class CLabelInfo
	{
	public:
		CLabelInfo(const XMLNode& Node=XMLNode::emptyNode());
	
		std::string CatalogNumber() const;
		CLabel Label() const;
	
	private:
		std::string m_CatalogNumber;
		CLabel m_Label;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CLabelInfo& LabelInfo);

#endif


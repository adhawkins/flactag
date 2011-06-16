#ifndef _MUSICBRAINZ4_LABEL_INFO_H
#define _MUSICBRAINZ4_LABEL_INFO_H

#include <string>
#include <iostream>

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CLabel;

	class CLabelInfo
	{
	public:
		CLabelInfo(const XMLNode& Node=XMLNode::emptyNode());
		CLabelInfo(const CLabelInfo& Other);
		CLabelInfo& operator =(const CLabelInfo& Other);
		~CLabelInfo();

		std::string CatalogNumber() const;
		CLabel *Label() const;

	private:
		void Cleanup();

		std::string m_CatalogNumber;
		CLabel *m_Label;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CLabelInfo& LabelInfo);

#endif


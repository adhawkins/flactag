#ifndef _MBADH_MEDIUM_H
#define _MBADH_MEDIUM_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "DiscList.h"
#include "TrackList.h"

namespace MusicBrainzADH
{
	class CMedium
	{
	public:
		CMedium(const XMLNode& Node=XMLNode::emptyNode());
	
		int Position() const;
		std::string Format() const;
		std::string Title() const;
		CDiscList DiscList() const;
		CTrackList TrackList() const;
	
		bool ContainsDiscID(const std::string& DiscID) const;
				
	private:
		int m_Position;
		std::string m_Format;
		std::string m_Title;
		CDiscList m_DiscList;
		CTrackList m_TrackList;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CMedium& Medium);

#endif

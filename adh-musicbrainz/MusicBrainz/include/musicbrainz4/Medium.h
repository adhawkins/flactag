#ifndef _MUSICBRAINZ4_MEDIUM_H
#define _MUSICBRAINZ4_MEDIUM_H

#include <string>
#include <iostream>

#include "GenericList.h"

#include "xmlParser.h"

namespace MusicBrainz4
{
	class CDisc;
	class CTrack;

	class CMedium
	{
	public:
		CMedium(const XMLNode& Node=XMLNode::emptyNode());
		CMedium(const CMedium& Other);
		CMedium& operator =(const CMedium& Other);
		~CMedium();

		std::string Title() const;
		int Position() const;
		std::string Format() const;
		CGenericList<CDisc> *DiscList() const;
		CGenericList<CTrack> *TrackList() const;

		bool ContainsDiscID(const std::string& DiscID) const;

	private:
		void Cleanup();

		std::string m_Title;
		int m_Position;
		std::string m_Format;
		CGenericList<CDisc> *m_DiscList;
		CGenericList<CTrack> *m_TrackList;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CMedium& Medium);

#endif

#ifndef _FREEDB_DISC_H
#define _FREEDB_DISC_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "GenericList.h"

namespace MusicBrainz4
{
	class CNoneMBTrack;

	class CFreeDBDisc
	{
	public:
		CFreeDBDisc(const XMLNode& Node);
		CFreeDBDisc(const CFreeDBDisc& Other);
		CFreeDBDisc& operator =(const CFreeDBDisc& Other);
		~CFreeDBDisc();

		std::string ID() const;
		std::string Title() const;
		std::string Artist() const;
		std::string Category() const;
		std::string Year() const;
		CGenericList<CNoneMBTrack> *NoneMBTrackList() const;

	private:
		void Cleanup();

		std::string m_ID;
		std::string m_Title;
		std::string m_Artist;
		std::string m_Category;
		std::string m_Year;
		CGenericList<CNoneMBTrack> *m_NoneMBTrackList;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CFreeDBDisc& FreeDBDisc);

#endif

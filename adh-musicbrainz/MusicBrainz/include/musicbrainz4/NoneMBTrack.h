#ifndef _MUSICBRAINZ4_NONE_MB_TRACK_H
#define _MUSICBRAINZ4_NONE_MB_TRACK_H

#include <string>
#include <iostream>

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CNoneMBTrack
	{
	public:
		CNoneMBTrack(const XMLNode& Node);
		CNoneMBTrack(const CNoneMBTrack& Other);
		CNoneMBTrack& operator =(const CNoneMBTrack& Other);

		std::string Title() const;
		std::string Artist() const;
		std::string Length() const;

	private:
		std::string m_Title;
		std::string m_Artist;
		std::string m_Length;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CNoneMBTrack& NoneMBTrack);

#endif

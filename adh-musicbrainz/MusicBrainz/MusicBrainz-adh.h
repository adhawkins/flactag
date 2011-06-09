#ifndef _MBADH_MUSICBRAINZ_ADH_H
#define _MBADH_MUSICBRAINZ_ADH_H

#include <string>

#include "GenericList.h"
#include "Release.h"
#include "Metadata.h"

namespace MusicBrainzADH
{
	class CMusicBrainzADH
	{
	public:
		CMusicBrainzADH(const std::string& Server="www.musicbrainz.org");

		CGenericList<CRelease> LookupDiscID(const std::string& DiscID);
		CRelease LookupRelease(const std::string& Release);

	private:
		std::string m_Server;

		CMetadata PerformQuery(const std::string& Query);
	};
}

#endif

#ifndef _MBADH_MUSICBRAINZ_ADH_H
#define _MBADH_MUSICBRAINZ_ADH_H

#include <string>

#include "GenericList.h"
#include "Release.h"

namespace MusicBrainzADH
{
	class CMusicBrainzADH
	{
	public:
		CGenericList<CRelease> LookupDiscID(const std::string& DiscID);
		CRelease LookupRelease(const std::string& Release);
	};
}

#endif

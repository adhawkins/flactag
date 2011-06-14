#ifndef _MUSICBRAINZ4_QUERY_H
#define _MUSICBRAINZ4_QUERY_H

#include <string>

#include "GenericList.h"
#include "Release.h"
#include "Metadata.h"

#include "xmlParser.h"

namespace MusicBrainz4
{
	class CQuery
	{
	public:
		CQuery(const std::string& Server="www.musicbrainz.org");

		CGenericList<CRelease> LookupDiscID(const std::string& DiscID);
		CRelease LookupRelease(const std::string& Release);

	private:
		std::string m_Server;

		CMetadata PerformQuery(const std::string& Query);
		void WaitRequest() const;
	};
}

#endif

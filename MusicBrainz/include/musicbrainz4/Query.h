#ifndef _MUSICBRAINZ4_QUERY_H
#define _MUSICBRAINZ4_QUERY_H

#include <string>
#include <map>

#include "musicbrainz4/GenericList.h"

#include "musicbrainz4/Release.h"
#include "musicbrainz4/Metadata.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CQuery
	{
	public:
		typedef std::map<std::string,std::string> tParamMap;

		CQuery(const std::string& Server="www.musicbrainz.org");

		CGenericList<CRelease> LookupDiscID(const std::string& DiscID);
		CRelease LookupRelease(const std::string& Release);
		CMetadata Query(const std::string& Resource,const std::string& ID,const tParamMap& Params=tParamMap());

	private:
		std::string m_Server;

		CMetadata PerformQuery(const std::string& Query);
		void WaitRequest() const;
	};
}

#endif

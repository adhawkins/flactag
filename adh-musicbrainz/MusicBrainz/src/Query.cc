//http://bugs.musicbrainz.org/browser/mmd-schema/trunk/schema/musicbrainz_mmd-2.0.rng

#include "musicbrainz4/Query.h"

#include <sstream>
#include <iostream>

#include <string.h>
#include <sys/time.h>

#include "musicbrainz4/HTTPFetch.h"
#include "musicbrainz4/Disc.h"

MusicBrainz4::CQuery::CQuery(const std::string& Server)
:	m_Server(Server)
{
}

MusicBrainz4::CMetadata MusicBrainz4::CQuery::PerformQuery(const std::string& Query)
{
	WaitRequest();
	
	CMetadata Metadata;

	CHTTPFetch Fetch(m_Server);

	int Ret=Fetch.Fetch(Query);
	if (Ret>0)
	{
		std::vector<unsigned char> Data=Fetch.Data();
		std::string strData(Data.begin(),Data.end());

		XMLResults Results;
		XMLNode TopNode=XMLNode::parseString(strData.c_str(), 0, &Results);
		if (Results.error==eXMLErrorNone)
		{
			XMLNode MetadataNode=TopNode.getChildNode("metadata");
			if (!MetadataNode.isEmpty())
			{
				Metadata=CMetadata(MetadataNode);
			}
		}
	}

	return Metadata;

}

MusicBrainz4::CGenericList<MusicBrainz4::CRelease> MusicBrainz4::CQuery::LookupDiscID(const std::string& DiscID)
{
	//Will this work soon (and return disc IDs as well)?
	//http://www.musicbrainz.org/ws/2/discid/arIS30RPWowvwNEqsqdDnZzDGhk-?inc=artists+labels+recordings+release-groups+artist-credits

	MusicBrainz4::CGenericList<MusicBrainz4::CRelease> ReleaseList;

	std::stringstream os;
	os << "/ws/2/discid/" << DiscID;
	CMetadata Metadata=PerformQuery(os.str());

	CDisc *Disc=Metadata.Disc();
	if (Disc && Disc->ReleaseList())
		ReleaseList=*Disc->ReleaseList();

	return ReleaseList;
}

MusicBrainz4::CRelease MusicBrainz4::CQuery::LookupRelease(const std::string& ReleaseID)
{
	MusicBrainz4::CRelease Release;

	std::stringstream os;
	os << "/ws/2/release/" << ReleaseID << "?inc=artists+labels+recordings+release-groups+url-rels+discids+artist-credits";

	CMetadata Metadata=PerformQuery(os.str());
	if (Metadata.Release())
		Release=*Metadata.Release();

	return Release;
}

void MusicBrainz4::CQuery::WaitRequest() const
{
	if (m_Server.find("musicbrainz.org")!=std::string::npos)
	{
		static struct timeval LastRequest;
		const int TimeBetweenRequests=2;
	
		struct timeval TimeNow;
		gettimeofday(&TimeNow,0);

		if (LastRequest.tv_sec!=0 || LastRequest.tv_usec!=0)
		{
			struct timeval Diff;
	
			do
			{
				gettimeofday(&TimeNow,0);
				timersub(&TimeNow,&LastRequest,&Diff);
	
				if (Diff.tv_sec<TimeBetweenRequests)
					usleep(100000);
			}	while (Diff.tv_sec<TimeBetweenRequests);
		}

		memcpy(&LastRequest,&TimeNow,sizeof(LastRequest));
	}
}

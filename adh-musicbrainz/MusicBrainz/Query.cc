//http://bugs.musicbrainz.org/browser/mmd-schema/trunk/schema/musicbrainz_mmd-2.0.rng

#include "Query.h"

#include <sstream>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "HTTPFetch.h"

#include "Disc.h"

MusicBrainz4::CQuery::CQuery(const std::string& Server)
:	m_Server(Server)
{
}

MusicBrainz4::CMetadata MusicBrainz4::CQuery::PerformQuery(const std::string& Query)
{
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
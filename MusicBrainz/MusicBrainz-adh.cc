#include "MusicBrainz-adh.h"

#include <sstream>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "HTTPFetch.h"

#include "Disc.h"

MusicBrainzADH::CMusicBrainzADH::CMusicBrainzADH(const std::string& Server)
:	m_Server(Server)
{
}

MusicBrainzADH::CMetadata MusicBrainzADH::CMusicBrainzADH::PerformQuery(const std::string& Query)
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

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelease> MusicBrainzADH::CMusicBrainzADH::LookupDiscID(const std::string& DiscID)
{
	//Will this work soon (and return disc IDs as well)?
	//http://www.musicbrainz.org/ws/2/discid/arIS30RPWowvwNEqsqdDnZzDGhk-?inc=artists+labels+recordings+release-groups+artist-credits

	MusicBrainzADH::CGenericList<MusicBrainzADH::CRelease> ReleaseList;

	std::stringstream os;
	os << "/ws/2/discid/" << DiscID;
	CMetadata Metadata=PerformQuery(os.str());

	CDisc *Disc=Metadata.Disc();
	if (Disc && Disc->ReleaseList())
		ReleaseList=*Disc->ReleaseList();

	return ReleaseList;
}

MusicBrainzADH::CRelease MusicBrainzADH::CMusicBrainzADH::LookupRelease(const std::string& ReleaseID)
{
	MusicBrainzADH::CRelease Release;

	std::stringstream os;
	os << "/ws/2/release/" << ReleaseID << "?inc=artists+labels+recordings+release-groups+url-rels+discids+artist-credits";

	CMetadata Metadata=PerformQuery(os.str());
	if (Metadata.Release())
		Release=*Metadata.Release();

	return Release;
}

#include "MusicBrainz-adh.h"

#include <sstream>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "HTTPFetch.h"

#include "GenericList.h"
#include "Release.h"
#include "Metadata.h"
#include "Disc.h"

MusicBrainzADH::CGenericList<MusicBrainzADH::CRelease> MusicBrainzADH::CMusicBrainzADH::LookupDiscID(const std::string& DiscID)
{
	//Will this work soon (and return disc IDs as well)?
	//http://www.musicbrainz.org/ws/2/discid/arIS30RPWowvwNEqsqdDnZzDGhk-?inc=artists+labels+recordings+release-groups+artist-credits

	MusicBrainzADH::CGenericList<MusicBrainzADH::CRelease> ReleaseList;

	std::stringstream os;
	os << "/ws/2/discid/" << DiscID;

	CHTTPFetch Fetch("www.musicbrainz.org");

	int Ret=Fetch.Fetch(os.str());
	if (Ret>0)
	{
		std::vector<unsigned char> Data=Fetch.Data();

		XMLResults Results;
		XMLNode TopNode=XMLNode::parseString((const char *)&Data[0], 0, &Results);
		if (Results.error==eXMLErrorNone)
		{
			XMLNode MetadataNode=TopNode.getChildNode("metadata");
			if (!MetadataNode.isEmpty())
			{
				CMetadata Metadata(MetadataNode);

				CDisc *Disc=Metadata.Disc();
				if (Disc && Disc->ReleaseList())
					ReleaseList=*Disc->ReleaseList();
			}
		}
	}

	return ReleaseList;
}

MusicBrainzADH::CRelease MusicBrainzADH::CMusicBrainzADH::LookupRelease(const std::string& ReleaseID)
{
	MusicBrainzADH::CRelease Release;

	std::stringstream os;
	os << "/ws/2/release/" << ReleaseID << "?inc=artists+labels+recordings+release-groups+url-rels+discids+artist-credits";

	CHTTPFetch Fetch("www.musicbrainz.org");

	int Ret=Fetch.Fetch(os.str());

	if (Ret>0)
	{
		std::vector<unsigned char> Data=Fetch.Data();

		XMLResults Results;
		XMLNode TopNode=XMLNode::parseString((const char *)&Data[0], 0, &Results);
		if (Results.error==eXMLErrorNone)
		{
			XMLNode MetadataNode=TopNode.getChildNode("metadata");
			if (!MetadataNode.isEmpty())
			{
				CMetadata Metadata(MetadataNode);
				if (Metadata.Release())
					Release=*Metadata.Release();
			}
		}
	}

	return Release;
}

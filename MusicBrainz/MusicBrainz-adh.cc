#include "MusicBrainz-adh.h"

#include <sstream>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "HTTPFetch.h"
#include "ReleaseList.h"

CReleaseList CMusicBrainzADH::LookupDiscID(const std::string& DiscID)
{
	//Will this work soon (and return disc IDs as well)?
	//http://www.musicbrainz.org/ws/2/discid/arIS30RPWowvwNEqsqdDnZzDGhk-?inc=artists+labels+recordings+release-groups+artist-credits
	
	CReleaseList ReleaseList;
	
	std::stringstream os;
	os << "/ws/2/discid/" << DiscID;
	
	CHTTPFetch Fetch("www.musicbrainz.org");

	int Ret=Fetch.Fetch(os.str());	
	if (Ret>0)
	{
		std::vector<unsigned char> Data=Fetch.Data();

		XMLNode TopNode=XMLNode::parseString((const char *)&Data[0]);			
		XMLNode MetadataNode=TopNode.getChildNode("metadata");
		XMLNode DiscNode=MetadataNode.getChildNode("disc");
		XMLNode ReleaseListNode=DiscNode.getChildNode("release-list");
			
		ReleaseList=CReleaseList(ReleaseListNode);
	}
	
	return ReleaseList;
}		

CRelease CMusicBrainzADH::LookupRelease(const std::string& ReleaseID)
{
	CRelease Release;
	
	std::stringstream os;
	os << "/ws/2/release/" << ReleaseID << "?inc=artists+labels+recordings+release-groups+url-rels+discids+artist-credits";

	CHTTPFetch Fetch("www.musicbrainz.org");

	int Ret=Fetch.Fetch(os.str());	
		
	if (Ret>0)
	{
		std::vector<unsigned char> Data=Fetch.Data();

		XMLNode TopNode=XMLNode::parseString((const char *)&Data[0]);			
		XMLNode MetadataNode=TopNode.getChildNode("metadata");
		XMLNode ReleaseNode=MetadataNode.getChildNode("release");
		Release=CRelease(ReleaseNode);
	}
		
	return Release;
}		

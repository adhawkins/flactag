#include "MusicBrainz-adh.h"

#include <sstream>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "HTTPFetch.h"
#include "ReleaseList.h"

CReleaseList CMusicBrainzADH::LookupDiscID(const std::string& DiscID)
{
	CReleaseList ReleaseList;
	
	std::stringstream os;
	os << "/ws/2/discid/" << DiscID;
	
	CHTTPFetch Fetch("www.musicbrainz.org");

	int Ret=Fetch.Fetch(os.str());	
	std::cout << "Fetch returns: " << Ret << std::endl;
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
	os << "/ws/2/release/" << ReleaseID << "?inc=recordings+artists+artist-credits+url-rels+discids";
	
	std::cout << "Query: '" << os.str() << "'" << std::endl;
		
	CHTTPFetch Fetch("www.musicbrainz.org");

	int Ret=Fetch.Fetch(os.str());	
	std::cout << "Fetch returns: " << Ret << std::endl;
	if (Ret>0)
	{
		std::vector<unsigned char> Data=Fetch.Data();

		XMLNode TopNode=XMLNode::parseString((const char *)&Data[0]);			
		std::cout << "Top node: " << std::endl << TopNode.createXMLString(true) << std::endl;
	}
		
	return Release;
}		

#include <iostream>

#include "MusicBrainz-adh.h"
#include "ReleaseList.h"

int main(int argc, const char *argv[])
{
	CMusicBrainzADH MB;
	
	std::string DiscID="arIS30RPWowvwNEqsqdDnZzDGhk-";
		
	if (argc==2)
		DiscID=argv[1];
		
	CReleaseList ReleaseList=MB.LookupDiscID(DiscID);
	
	std::vector<CRelease>Releases=ReleaseList.Releases();
	std::vector<CRelease>::const_iterator ThisRelease=Releases.begin();
	while (ThisRelease!=Releases.end())
	{
		CRelease Release=(*ThisRelease);
		
		std::cout << "Found release ID: '" << Release.ID() << "'" << std::endl;

		CRelease FullRelease=MB.LookupRelease(Release.ID());
		
		++ThisRelease;
	}
	
	return 0;
}
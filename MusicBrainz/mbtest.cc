#include <iostream>

#include "MusicBrainz-adh.h"
#include "ReleaseList.h"

int main(int argc, const char *argv[])
{
	CMusicBrainzADH MB;

	//CRelease Test=MB.LookupRelease("8fd13191-2d9a-4670-b789-0c99a06278e0");
	//CRelease Test=MB.LookupRelease("ae8c2094-f3a8-45f8-8c1b-09d069425526");
	//std::cout << Test << std::endl;
	//return 0;
		
	std::string DiscID="arIS30RPWowvwNEqsqdDnZzDGhk-";
	//DiscID="kXyckpXOUugZwZXFrAo5jbsap88-";
	
	if (argc==2)
		DiscID=argv[1];
		
	CReleaseList ReleaseList=MB.LookupDiscID(DiscID);
	
	std::vector<CRelease>Releases=ReleaseList.Releases();
	std::vector<CRelease>::const_iterator ThisRelease=Releases.begin();
	while (ThisRelease!=Releases.end())
	{
		CRelease Release=(*ThisRelease);
		
		CRelease FullRelease=MB.LookupRelease(Release.ID());
		
		std::cout << FullRelease << std::endl;
			
		++ThisRelease;
	}
	
	return 0;
}
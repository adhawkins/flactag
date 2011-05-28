#include <iostream>

#include "MusicBrainz-adh.h"
#include "ReleaseList.h"

int main(int argc, const char *argv[])
{
	MusicBrainzADH::CMusicBrainzADH MB;

	//MusicBrainzADH::CRelease Test=MB.LookupRelease("8fd13191-2d9a-4670-b789-0c99a06278e0");
	//MusicBrainzADH::CRelease Test=MB.LookupRelease("ae8c2094-f3a8-45f8-8c1b-09d069425526");
	//std::cout << Test << std::endl;
	//return 0;
		
	std::string DiscID="arIS30RPWowvwNEqsqdDnZzDGhk-";
	//DiscID="kXyckpXOUugZwZXFrAo5jbsap88-";
	
	if (argc==2)
		DiscID=argv[1];
		
	MusicBrainzADH::CReleaseList ReleaseList=MB.LookupDiscID(DiscID);
	
	std::vector<MusicBrainzADH::CRelease>Releases=ReleaseList.Releases();
	std::vector<MusicBrainzADH::CRelease>::const_iterator ThisRelease=Releases.begin();
	while (ThisRelease!=Releases.end())
	{
		MusicBrainzADH::CRelease Release=(*ThisRelease);
		
		MusicBrainzADH::CRelease FullRelease=MB.LookupRelease(Release.ID());
		
		std::cout << "Full release: " << std::endl;
			
		std::cout << FullRelease << std::endl;
			
		std::cout << "Release group title: '" << FullRelease.ReleaseGroup().Title() << "'" << std::endl;
			
		std::cout << std::endl << std::endl << "Media matching " << DiscID << ":" << std::endl;
			
		std::vector<MusicBrainzADH::CMedium> Media=FullRelease.MediaMatchingDiscID(DiscID);
		std::vector<MusicBrainzADH::CMedium>::const_iterator ThisMedium=Media.begin();
		while (ThisMedium!=Media.end())
		{
			std::cout << *ThisMedium << std::endl;
				
			++ThisMedium;
		}
			
		std::cout << std::endl << std::endl;
		
		++ThisRelease;
	}
	
	return 0;
}

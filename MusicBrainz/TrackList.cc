#include "ReleaseList.h"

#include <iostream>

#include "xmlParser/xmlParser.h"

CTrackList::CTrackList(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Track list node: " << std::endl << Node.createXMLString(true) << std::endl;
			
		int nTracks=Node.nChildNode("track");
		
		for (int count=0;count<nTracks;count++)
		{
			XMLNode TrackNode=Node.getChildNode("track",count);
			m_Tracks.push_back(CTrack(TrackNode));
		}
	}
}

std::vector<CTrack> CTrackList::Tracks() const
{
	return m_Tracks;
}

std::ostream& operator << (std::ostream& os, const CTrackList& TrackList)
{
	os << "Track list:" << std::endl;
		
	std::vector<CTrack>::const_iterator ThisTrack=TrackList.m_Tracks.begin();
	while (ThisTrack!=TrackList.m_Tracks.end())
	{
		os << *ThisTrack;
		
		++ThisTrack;
	}
	
	return os;
}

#include "ReleaseList.h"

#include <iostream>

#include "xmlParser/xmlParser.h"

MusicBrainzADH::CTrackList::CTrackList(const XMLNode& Node)
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

std::vector<MusicBrainzADH::CTrack> MusicBrainzADH::CTrackList::Tracks() const
{
	return m_Tracks;
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CTrackList& TrackList)
{
	os << "Track list:" << std::endl;
		
	std::vector<MusicBrainzADH::CTrack> Tracks=TrackList.Tracks();
	std::vector<MusicBrainzADH::CTrack>::const_iterator ThisTrack=Tracks.begin();
	while (ThisTrack!=Tracks.end())
	{
		os << *ThisTrack;
		
		++ThisTrack;
	}
	
	return os;
}

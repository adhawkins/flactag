#ifndef _MBADH_TRACK_H
#define _MBADH_TRACK_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

namespace MusicBrainzADH
{
	class CRecording;
	
	class CTrack
	{
	public:
		CTrack(const XMLNode& Node=XMLNode::emptyNode());
		CTrack(const CTrack& Other);
		CTrack& operator =(const CTrack& Other);
		~CTrack();
	
		int Position() const;
		std::string Title() const;
		CRecording *Recording() const;
			
	private:
		void Cleanup();
		
		int m_Position;
		std::string m_Title;
		CRecording *m_Recording;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CTrack& Track);

#endif

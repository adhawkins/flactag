#ifndef _MBADH_TRACK_H
#define _MBADH_TRACK_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "Recording.h"

namespace MusicBrainzADH
{
	class CTrack
	{
	public:
		CTrack(const XMLNode& Node=XMLNode::emptyNode());
	
		int Position() const;
		std::string Title() const;
		CRecording Recording() const;
			
	private:
		int m_Position;
		std::string m_Title;
		CRecording m_Recording;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CTrack& Track);

#endif

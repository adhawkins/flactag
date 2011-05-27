#ifndef _TRACK_H
#define _TRACK_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "Recording.h"

class CTrack
{
public:
	CTrack(const XMLNode& Node=XMLNode::emptyNode());

	std::string Position() const;
	CRecording Recording() const;
		
private:
	std::string m_Position;
	CRecording m_Recording;
		
	friend std::ostream& operator << (std::ostream& os, const CTrack& Track);
};

#endif

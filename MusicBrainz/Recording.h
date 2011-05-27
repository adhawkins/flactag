#ifndef _RECORDING_H
#define _RECORDING_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "ArtistCredit.h"

class CRecording
{
public:
	CRecording(const XMLNode& Node=XMLNode::emptyNode());

	std::string ID() const;
	std::string Title() const;
	std::string Length() const;
	CArtistCredit ArtistCredit() const;
		
private:
	std::string m_ID;
	std::string m_Title;
	std::string m_Length;
	CArtistCredit m_ArtistCredit;
		
	friend std::ostream& operator << (std::ostream& os, const CRecording& Recording);
};

#endif

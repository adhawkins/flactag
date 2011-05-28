#ifndef _MBADH_RECORDING_H
#define _MBADH_RECORDING_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "ArtistCredit.h"

namespace MusicBrainzADH
{
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
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CRecording& Recording);

#endif

#ifndef _ISRC_H
#define _ISRC_H

#include "GenericList.h"
#include "Recording.h"

namespace MusicBrainzADH
{
	class CISRC
	{
	public:
		CISRC(const XMLNode& Node=XMLNode::emptyNode());
		CISRC(const CISRC& Other);
		CISRC& operator =(const CISRC& Other);
		~CISRC();
		
		std::string ID() const;
		CGenericList<CRecording> *RecordingList() const;
		
	private:
		void Cleanup();
		
		std::string m_ID;
		CGenericList<CRecording> *m_RecordingList;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CISRC& ISRC);

#endif

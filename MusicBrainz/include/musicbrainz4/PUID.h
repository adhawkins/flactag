#ifndef _PUID_H
#define _PUID_H

#include <string>

#include "GenericList.h"
#include "Recording.h"

#include "xmlParser.h"

namespace MusicBrainz4
{
	class CPUID
	{
	public:
		CPUID(const XMLNode& Node=XMLNode::emptyNode());
		CPUID(const CPUID& Other);
		CPUID& operator =(const CPUID& Other);
		~CPUID();

		std::string ID() const;
		CGenericList<CRecording> *RecordingList() const;

	private:
		void Cleanup();

		std::string m_ID;
		CGenericList<CRecording> *m_RecordingList;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CPUID& PUID);

#endif

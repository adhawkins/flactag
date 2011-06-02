#ifndef _MBADH_RELATION_H
#define _MBADH_RELATION_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "GenericList.h"

namespace MusicBrainzADH
{
	class CAttribute;
	class CArtist;
	class CRelease;
	class CReleaseGroup;
	class CRecording;
	class CLabel;
	class CWork;
	
	class CRelation
	{
	public:
		CRelation(const XMLNode& Node=XMLNode::emptyNode());
		CRelation(const CRelation& Other);
		CRelation& operator =(const CRelation& Other);
		~CRelation();
		
		std::string Type() const;
		std::string Target() const;
		std::string Direction() const;
		CGenericList<CAttribute> *AttributeList() const;
		std::string Begin() const;
		std::string End() const;
		CArtist *Artist() const;
		CRelease *Release() const;
		CReleaseGroup *ReleaseGroup() const;
		CRecording *Recording() const;
		CLabel *Label() const;
		CWork *Work() const;
			
	private:
		void Cleanup();
		
		std::string m_Type;
		std::string m_Target;
		std::string m_Direction;
		CGenericList<CAttribute> *m_AttributeList;
		std::string m_Begin;
		std::string m_End;
		CArtist *m_Artist;
		CRelease *m_Release;
		CReleaseGroup *m_ReleaseGroup;
		CRecording *m_Recording;
		CLabel *m_Label;
		CWork *m_Work;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CRelation& Relation);

#endif

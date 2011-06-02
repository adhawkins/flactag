#ifndef _CDSTUB_H
#define _CDSTUB_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "GenericList.h"

namespace MusicBrainzADH
{
	class CNoneMBTrack;
	
	class CCDStub
	{
	public:
		CCDStub(const XMLNode& Node);
		CCDStub(const CCDStub& Other);
		CCDStub& operator =(const CCDStub& Other);
		~CCDStub();

		std::string ID() const;
		std::string Title() const;
		std::string Artist() const;
		std::string Barcode() const;
		std::string Comment() const;
		CGenericList<CNoneMBTrack> *NoneMBTrackList() const;
	
	private:
		void Cleanup();
		
		std::string m_ID;
		std::string m_Title;
		std::string m_Artist;
		std::string m_Barcode;
		std::string m_Comment;
		CGenericList<CNoneMBTrack> *m_NoneMBTrackList;
		
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainzADH::CCDStub& CDStub);

#endif

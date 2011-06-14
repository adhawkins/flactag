#ifndef _MBADH_NAME_CREDIT_H
#define _MBADH_NAME_CREDIT_H

#include <string>
#include <iostream>

#include "xmlParser.h"

namespace MusicBrainz4
{
	class CArtist;

	class CNameCredit
	{
	public:
		CNameCredit(const XMLNode& Node=XMLNode::emptyNode());
		CNameCredit(const CNameCredit& Other);
		CNameCredit& operator =(const CNameCredit& Other);
		~CNameCredit();

		std::string JoinPhrase() const;
		std::string Name() const;
		CArtist *Artist() const;

	private:
		void Cleanup();

		std::string m_JoinPhrase;
		std::string m_Name;
		CArtist *m_Artist;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CNameCredit& NameCredit);

#endif

#ifndef _NAME_CREDIT_H
#define _NAME_CREDIT_H

#include <string>
#include <iostream>

#include "xmlParser/xmlParser.h"

#include "Artist.h"

class CNameCredit
{
public:
	CNameCredit(const XMLNode& Node=XMLNode::emptyNode());

	std::string JoinPhrase() const;
	std::string Name() const;
	CArtist Artist() const;

private:
	std::string m_JoinPhrase;
	std::string m_Name;
	CArtist m_Artist;

	friend std::ostream& operator << (std::ostream& os, const CNameCredit& NameCredit);
};

#endif

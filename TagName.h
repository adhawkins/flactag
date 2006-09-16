#ifndef _TAG_NAME_H
#define _TAG_NAME_H

#include <string>
#include <map>

class CTagName
{
public:
	CTagName(const std::string& Name, int Number);
	CTagName(const std::string& Name);

	bool operator <(const CTagName& Other) const;
	bool operator >(const CTagName& Other) const;
	bool operator ==(const CTagName& Other) const;
	
	std::string Name() const;
	int Number() const;	
	std::string CTagName::String() const;

private:
	std::string m_Name;
	int m_Number;
	
	bool SpecialTag() const;
};

typedef std::map<CTagName,std::string> tTagMap;
typedef tTagMap::const_iterator tTagMapConstIterator;
typedef tTagMap::iterator tTagMapIterator;

#endif

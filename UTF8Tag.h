#ifndef _UTF8_TAG
#define _UTF8_TAG

#include <string>

class CUTF8Tag
{
public:
	CUTF8Tag(const std::string& Value="");
	
	bool operator ==(const CUTF8Tag& Other) const;
	bool operator !=(const CUTF8Tag& Other) const;

	bool empty() const;
	
	std::string UTF8Value() const;
	std::string ISO88591Value() const;
	
protected:
	std::string m_Value;
};

#endif

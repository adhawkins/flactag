#ifndef _UTF8_TAG
#define _UTF8_TAG

#include <string>

class CUTF8Tag
{
public:
	CUTF8Tag(const std::string& UTF8Value="");
	
	bool operator ==(const CUTF8Tag& Other) const;
	bool operator !=(const CUTF8Tag& Other) const;

	bool empty() const;
	
	std::string UTF8Value() const;
	std::string DisplayValue() const;
	
protected:
	std::string m_UTF8Value;
	std::string m_DisplayValue;
		
	void Convert();
};

#endif

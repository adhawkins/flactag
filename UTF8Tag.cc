#include "UTF8Tag.h"

#include <locale.h>
#include <langinfo.h>

CUTF8Tag::CUTF8Tag(const std::string& UTF8Value)
:	m_UTF8Value(UTF8Value)
{
	Convert();
}

void CUTF8Tag::Convert()
{
	if (!m_UTF8Value.empty())
	{
		setlocale(LC_ALL,  "" );
		char *Codeset=nl_langinfo(CODESET);
			
		char *In=new char[m_UTF8Value.length()+1];
		strcpy(In,m_UTF8Value.c_str());
		
		char *Out=new char[m_UTF8Value.length()+1];
		memset(Out,0,m_UTF8Value.length()+1);
		size_t InLeft=m_UTF8Value.length();
		size_t OutLeft=m_UTF8Value.length();
		
		char *InBuff=In;
		char *OutBuff=Out;
		
		iconv_t Convert=iconv_open(Codeset,"UTF-8");
		if ((iconv_t)-1!=Convert)
		{
			if ((size_t)-1!=iconv(Convert,&InBuff,&InLeft,&OutBuff,&OutLeft))
			{
				if (OutLeft>=sizeof(char))
				    *OutBuff='\0';
	
				m_DisplayValue=Out;
			}		    
			
			iconv_close(Convert);
		}
	
		if (In)
			free(In);
			
		if (Out)
			free(Out);
	}
}

bool CUTF8Tag::operator ==(const CUTF8Tag& Other) const
{
	return m_UTF8Value==Other.m_UTF8Value;
}

bool CUTF8Tag::operator !=(const CUTF8Tag& Other) const
{
	return !(*this==Other);
}

bool CUTF8Tag::empty() const
{
	return m_UTF8Value.empty();
}
	
std::string CUTF8Tag::UTF8Value() const
{
	return m_UTF8Value;
}

std::string CUTF8Tag::DisplayValue() const
{
	return m_DisplayValue;
}

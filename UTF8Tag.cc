#include "UTF8Tag.h"

CUTF8Tag::CUTF8Tag(const std::string& Value)
:	m_Value(Value)
{
}

bool CUTF8Tag::operator ==(const CUTF8Tag& Other) const
{
	return m_Value==Other.m_Value;
}

bool CUTF8Tag::operator !=(const CUTF8Tag& Other) const
{
	return !(*this==Other);
}

bool CUTF8Tag::empty() const
{
	return m_Value.empty();
}
	
std::string CUTF8Tag::UTF8Value() const
{
	return m_Value;
}

std::string CUTF8Tag::ISO88591Value() const
{
	std::string Ret;
		
	if (!m_Value.empty())
	{
		char *In=new char[m_Value.length()+1];
		strcpy(In,m_Value.c_str());
		
		char *Out=new char[m_Value.length()+1];
		memset(Out,0,m_Value.length()+1);
		size_t InLeft=m_Value.length();
		size_t OutLeft=m_Value.length();
		
		char *InBuff=In;
		char *OutBuff=Out;
		
		iconv_t Convert=iconv_open("ISO-8859-1","UTF-8");
		if ((iconv_t)-1!=Convert)
		{
			if ((size_t)-1!=iconv(Convert,&InBuff,&InLeft,&OutBuff,&OutLeft))
			{
				if (OutLeft>=sizeof(char))
				    *OutBuff='\0';
	
				Ret=Out;
			}		    
			
			iconv_close(Convert);
		}
	
		if (In)
			free(In);
			
		if (Out)
			free(Out);
	}
		
	return Ret;
}

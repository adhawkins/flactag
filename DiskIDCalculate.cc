#include "DiskIDCalculate.h"

#include <sstream>

#include "sha1.h"
#include "base64.h"

CDiskIDCalculate::CDiskIDCalculate(const CCuesheet& Cuesheet)
:	m_Cuesheet(Cuesheet)
{
	SHA_INFO sha;
	
	sha_init(&sha);
	
	char Temp[100];
	
	sprintf(Temp,"%02X",m_Cuesheet.FirstTrack());
	sha_update(&sha, (unsigned char *)Temp, strlen(Temp));
	
	sprintf(Temp,"%02X",m_Cuesheet.LastTrack());
	sha_update(&sha, (unsigned char *)Temp, strlen(Temp));

	sprintf(Temp,"%08lX",m_Cuesheet.Leadout());
	sha_update(&sha, (unsigned char *)Temp, strlen(Temp));
	
	for (int count=1;count<100;count++)
	{
		if (count<=m_Cuesheet.LastTrack())
		{
			CCuesheetTrack Track=m_Cuesheet.Track(count);
			sprintf(Temp,"%08lX",Track.Offset());
  	}
		else
			sprintf(Temp,"%08lX",0);
	
		sha_update(&sha, (unsigned char *)Temp, strlen(Temp));
	}
	
	unsigned char Digest[20];
	
	sha_final(Digest, &sha);
	
	unsigned long Size;
	unsigned char *Base64=rfc822_binary(Digest,20,&Size);
	char DiskID[100];
	memcpy(DiskID,(const char *)Base64,Size);
	DiskID[Size]='\0';
	m_DiskID=DiskID;
	free(Base64);
}

std::string CDiskIDCalculate::DiskID() const
{
	return m_DiskID;
}

std::string CDiskIDCalculate::SubmitURL() const
{ 
	std::stringstream os;

	os << "http://mm.musicbrainz.org/bare/cdlookup.html";
		
	os << "?id=" << m_DiskID;
	
	os << "&tracks=", m_Cuesheet.LastTrack(); 

	os << "&toc=" << m_Cuesheet.FirstTrack() << 
				"+" << m_Cuesheet.LastTrack() << "+" << m_Cuesheet.Leadout();
	
	for (int count=1;count<=m_Cuesheet.LastTrack();count++)
	{
		CCuesheetTrack Track=m_Cuesheet.Track(count);
		
		os << "+" << Track.Offset();
	} 
	
	return os.str();
}

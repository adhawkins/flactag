/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006 Andrew Hawkins
   
   This file is part of flactag.
   
   Flactag is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.
   
   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

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

	sprintf(Temp,"%02X",(int)m_Cuesheet.FirstTrack());
	sha_update(&sha, (unsigned char *)Temp, strlen(Temp));
	
	sprintf(Temp,"%02X",(int)m_Cuesheet.LastTrack());
	sha_update(&sha, (unsigned char *)Temp, strlen(Temp));

	sprintf(Temp,"%08lX",(unsigned long)m_Cuesheet.Leadout());
	sha_update(&sha, (unsigned char *)Temp, strlen(Temp));
	
	for (int count=1;count<100;count++)
	{
		if (count<=m_Cuesheet.LastTrack())
		{
			CCuesheetTrack Track=m_Cuesheet.Track(count);
			sprintf(Temp,"%08lX",(unsigned long)Track.Offset());
  	}
		else
			sprintf(Temp,"%08lX",(unsigned long)0);
	
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
	
	os << "&tracks=", (int)m_Cuesheet.LastTrack(); 

	os << "&toc=" << (int)m_Cuesheet.FirstTrack() << 
				"+" << (int)m_Cuesheet.LastTrack() << "+" << m_Cuesheet.Leadout();
	
	for (int count=1;count<=m_Cuesheet.LastTrack();count++)
	{
		CCuesheetTrack Track=m_Cuesheet.Track(count);
		
		os << "+" << Track.Offset();
	} 
	
	return os.str();
}

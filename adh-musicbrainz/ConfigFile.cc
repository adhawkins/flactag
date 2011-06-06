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

#include "ConfigFile.h"

#include <stdio.h>

CConfigFile::CConfigFile()
{
	m_Values["BasePath"]="";
	m_Values["SingleDiskFileName"]="";
	m_Values["MultiDiskFileName"]="";
	m_Values["DirectoryCreatePermissions"]="0755";
	m_Values["Server"]="musicbrainz.org";
}

std::string CConfigFile::Value(const std::string& Name) const
{
	std::string Value;
		
	std::map<std::string,std::string>::const_iterator ThisValue=m_Values.find(Name);
	if (m_Values.end()!=ThisValue)
		Value=(*ThisValue).second;
		
	return Value;
}

bool CConfigFile::LoadFile(const std::string& FileName)
{
	bool RetVal=false;
	
	FILE *fptr=fopen(FileName.c_str(),"rt");
	if (fptr)
	{
		RetVal=true;
	
		while (!feof(fptr))
		{
			char Buffer[1024];
		
			fgets(Buffer,sizeof(Buffer),fptr);
			if (!feof(fptr))
			{
				std::string TmpBuff=Buffer;
				std::string::size_type EqualsPos=TmpBuff.find("=");
				if (std::string::npos!=EqualsPos)
				{
					std::string Name=TmpBuff.substr(0,EqualsPos);
					std::string Value=TmpBuff.substr(EqualsPos+1);
					while (Value[Value.length()-1]=='\n' || Value[Value.length()-1]=='\r')
						Value=Value.substr(0,Value.length()-1);

					m_Values[Name]=Value;						
				}
			}
		}			
		
		fclose(fptr);
	}
	
	return RetVal;
}

bool CConfigFile::SaveFile(const std::string& FileName) const
{
	bool RetVal=false;
	
	FILE *fptr=fopen(FileName.c_str(),"wt");
	if (fptr)
	{
		std::map<std::string,std::string>::const_iterator ThisValue=m_Values.begin();
		while(m_Values.end()!=ThisValue)
		{
			std::string Name=(*ThisValue).first;
			std::string Value=(*ThisValue).second;
				
			fprintf(fptr,"%s=%s\n",Name.c_str(),Value.c_str());
			
			++ThisValue;
		}
		RetVal=true;
	}
	
	return RetVal;
}

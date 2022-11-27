/* --------------------------------------------------------------------------

	 flactag -- A tagger for single album FLAC files with embedded CUE sheets
							using data retrieved from the MusicBrainz service

	 Copyright (C) 2006-2022 Andrew Hawkins
	 Copyright (C) 2011-2012 Daniel Pocock

	 This file is part of flactag.

	 This program is free software: you can redistribute it and/or modify
	 it under the terms of the GNU General Public License as published by
	 the Free Software Foundation, either version 3 of the License, or
	 (at your option) any later version.

	 Flactag is distributed in the hope that it will be useful,
	 but WITHOUT ANY WARRANTY; without even the implied warranty of
	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	 Lesser General Public License for more details.

	 You should have received a copy of the GNU General Public
	 License along with this library; if not, write to the Free Software
	 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

		 $Id$

----------------------------------------------------------------------------*/

#include "ConfigFile.h"

#include <assert.h>
#include <stdio.h>
#include <strings.h>

CConfigFile::CConfigFile()
{
	m_Values[EntryLookup(tConfigEntry::BasePath)] = "";
	m_Values[EntryLookup(tConfigEntry::SingleDiskFileName)] = "";
	m_Values[EntryLookup(tConfigEntry::MultiDiskFileName)] = "";
	m_Values[EntryLookup(tConfigEntry::DirectoryCreatePermissions)] = "0755";
	m_Values[EntryLookup(tConfigEntry::Server)] = "musicbrainz.org";
	m_Values[EntryLookup(tConfigEntry::Port)] = "80";
	m_Values[EntryLookup(tConfigEntry::CreateCuesheetAfterRename)] = "0";
	m_Values[EntryLookup(tConfigEntry::IncludeAlbumDisambiguation)] = "yes";
	m_Values[EntryLookup(tConfigEntry::StandardiseArtists)] = "yes";
}

std::string CConfigFile::EntryLookup(CConfigFile::tConfigEntry Entry) const
{
	auto EntryName = m_EntryLookup.find(Entry);
	assert(EntryName != m_EntryLookup.end());

	return (*EntryName).second;
}

std::string CConfigFile::Value(CConfigFile::tConfigEntry Entry) const
{
	std::string Value;

	std::string EntryName = EntryLookup(Entry);
	std::map<std::string, std::string>::const_iterator ThisValue = m_Values.find(EntryName);
	if (m_Values.end() != ThisValue)
	{
		Value = (*ThisValue).second;
	}

	return Value;
}

bool CConfigFile::BoolValue(CConfigFile::tConfigEntry Entry) const
{
	std::string _val(Value(Entry));

	for(unsigned int i = 0; i < _val.size(); i++)
		_val[i] = std::tolower(_val[i]);

	if(_val == "1")
		return true;
	if(_val.compare("true") == 0)
		return true;
	if(_val.compare("yes") == 0)
		return true;

	return false;
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

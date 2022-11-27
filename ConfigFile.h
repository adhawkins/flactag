/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006-2012 Andrew Hawkins
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

#ifndef _CONFIG_FILE_H
#define _CONFIG_FILE_H

#include <map>
#include <string>

class CConfigFile
{
public:
  enum class tConfigEntry
  {
    BasePath,
    SingleDiskFileName,
    MultiDiskFileName,
    Server,
    Port,
    DirectoryCreatePermissions,
    CreateCuesheetAfterRename,
  };

  CConfigFile();

  bool LoadFile(const std::string &FileName);
  bool SaveFile(const std::string &FileName) const;

  std::string Value(tConfigEntry Entry) const;
  bool BoolValue(tConfigEntry Entry) const;

private:
  std::string EntryLookup(CConfigFile::tConfigEntry Entry) const;

  std::map<std::string, std::string> m_Values;
  const std::map<tConfigEntry, std::string> m_EntryLookup = {
      {tConfigEntry::BasePath, "BasePath"},
      {tConfigEntry::SingleDiskFileName, "SingleDiskFileName"},
      {tConfigEntry::MultiDiskFileName, "MultiDiskFileName"},
      {tConfigEntry::Server, "Server"},
      {tConfigEntry::Port, "Port"},
      {tConfigEntry::DirectoryCreatePermissions, "DirectoryCreatePermissions"},
      {tConfigEntry::CreateCuesheetAfterRename, "CreateCuesheetAfterRename"},
  };
};

#endif


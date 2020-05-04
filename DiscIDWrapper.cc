/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006-2007 Andrew Hawkins

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

#include "DiscIDWrapper.h"

CDiscIDWrapper::CDiscIDWrapper()
:	m_DiscID(discid_new())
{
}

CDiscIDWrapper::~CDiscIDWrapper()
{
	if (m_DiscID)
		discid_free(m_DiscID);
}

bool CDiscIDWrapper::FromDevice(const std::string& Device)
{
#if defined(DISCID_VERSION_MAJOR) && (DISCID_VERSION_MAJOR > 0 || (DISCID_VERSION_MAJOR == 0 && DISCID_VERSION_MINOR >= 4))
	return discid_read_sparse(m_DiscID,Device.c_str(),DISCID_FEATURE_READ);
#else
	return discid_read(m_DiscID,Device.c_str());
#endif
}

bool CDiscIDWrapper::FromCuesheet(const CCuesheet& Cuesheet)
{
	std::vector<int> Offsets;

	for (int count=Cuesheet.FirstTrack();count<=Cuesheet.LastTrack();count++)
		Offsets.push_back(Cuesheet.Track(count).Offset());

	return FromTOC(Cuesheet.FirstTrack(),Cuesheet.LastTrack(),Cuesheet.Leadout(),Offsets);
}

bool CDiscIDWrapper::FromTOC(int First, int Last, int Leadout, std::vector<int> Offsets)
{
	int *OffsetsArray=new int[Last+1];

	OffsetsArray[0]=Leadout;

	for (std::vector<int>::size_type count=0;count<Offsets.size();count++)
		OffsetsArray[count+1]=Offsets[count];

	bool RetVal=discid_put(m_DiscID,First,Last,OffsetsArray);

	delete[] OffsetsArray;

	return RetVal;
}

std::string CDiscIDWrapper::ID() const
{
	return discid_get_id(m_DiscID);
}

std::string CDiscIDWrapper::SubmitURL() const
{
	return discid_get_submission_url(m_DiscID);
}

std::string CDiscIDWrapper::Error() const
{
	return discid_get_error_msg(m_DiscID);
}

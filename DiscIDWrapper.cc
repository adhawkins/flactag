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
	return discid_read(m_DiscID,Device.c_str());
}

bool CDiscIDWrapper::FromTOC(int First, int Last, int Leadout, std::vector<int> Offsets)
{
	int *OffsetsArray=new int[100];
	
	OffsetsArray[0]=Leadout;
	
	for (std::vector<int>::size_type count=1;count<99;count++)
	{
		if (count<=Offsets.size())
			OffsetsArray[count]=Offsets[count-1];
		else
			OffsetsArray[count]=0;
	}
	
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

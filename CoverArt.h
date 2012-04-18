/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006-2008 Andrew Hawkins

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

#ifndef _COVERART_H
#define _COVERART_H

#include <string.h>

#include <string>

#include <jpeglib.h>
#include <jerror.h>

class CCoverArt
{
public:
	CCoverArt(const unsigned char *Data=0, size_t Length=0);
	CCoverArt(const CCoverArt& Other);
	~CCoverArt();

	CCoverArt& operator =(const CCoverArt& Other);
	bool operator ==(const CCoverArt& Other) const;
	bool operator !=(const CCoverArt& Other) const;
	operator bool() const;
	operator std::string() const;

	void SetArt(const unsigned char *Data, size_t Length, bool RetrieveDimensions);
	void Clear();
	unsigned char *Data() const;
	size_t Length() const;
	int Width() const;
	int Height() const;

	static void InitSource(j_decompress_ptr cinfo);
	static boolean FillInputBuffer(j_decompress_ptr cinfo);
	static void SkipInputData(j_decompress_ptr cinfo, long num_bytes);
	static void TermSource(j_decompress_ptr cinfo);
	static void JPEGMemorySource(j_decompress_ptr cinfo, const JOCTET * buffer, size_t bufsize);

private:
	void Free();
	void GetDimensions();

	unsigned char *m_Data;
	size_t m_Length;
	int m_Width;
	int m_Height;
};

#endif

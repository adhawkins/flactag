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

#include <stdio.h>
#include <stdlib.h>
#include "musicbrainz/musicbrainz.h"

int main(int argc, const char *argv[])
{
	if (argc==2)
	{
    MusicBrainz o;

    o.SetDevice(argv[1]);
    //o.SetDebug(1);
    
    if (o.Query(string(MBQ_GetCDTOC)))
    {
    	std::string RDF;
    	printf("%s\n",o.Data(MBE_TOCGetCDIndexId).c_str());
    }
    else
    {
    	std::string Error;
    		
			o.GetQueryError(Error);
			printf("Query failed: %s\n", Error.c_str());
		}
	}
	else
		printf("Usage: %s pathtocddevice\n",argv[0]);
		
  return 0;
}


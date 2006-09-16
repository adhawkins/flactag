#include <stdio.h>
#include <stdlib.h>
#include "musicbrainz/musicbrainz.h"

int main(int argc, const char *argv[])
{
	if (argc==2)
	{
    MusicBrainz o;
    bool        ret;

    o.SetDevice(argv[1]);
    o.SetDebug(1);
    
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


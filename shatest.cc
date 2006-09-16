#include "sha1.h"
#include "base64.h"

#include <string.h>

int main(int argc, const char *argv[])
{
	SHA_INFO sha;
	
	sha_init(&sha);
	
	char Temp[100];
	
	sprintf(Temp,"%02X",1);
	sha_update(&sha, (unsigned char *)Temp, strlen(Temp));
	
	sprintf(Temp,"%02X",13);
	sha_update(&sha, (unsigned char *)Temp, strlen(Temp));
	
	int Tracks[]={281765,0,14337,32372,54900,88362,116655,131152,156702,177475,193582,215662,236882,254497};

	int NumTracks=sizeof(Tracks)/sizeof(Tracks[0]);
	
	for (int count=0;count<100;count++)
	{
		if (count<NumTracks)
		{
			sprintf(Temp,"%08lX",Tracks[count]+150);
  		printf("Track %d = %d\n",count,Tracks[count]+150);
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
	free(Base64);
	
	printf("%s\n",DiskID);
}

#include <string>

#include "FlacInfo.h"
#include "DiskIDCalculate.h"

void GetSubmissionURL(const std::string& FlacFile);

int main(int argc, const char *argv[])
{
	if (argc==2)
		GetSubmissionURL(argv[1]);
	else
		printf("Usage: %s flacfile\n",argv[0]);
}

void GetSubmissionURL(const std::string& FlacFile)
{
	CFlacInfo FlacInfo;
	
	FlacInfo.SetFileName(FlacFile);
	FlacInfo.Read();
	
	printf("Calculating\n");
	CDiskIDCalculate Calc(FlacInfo.Cuesheet());
	printf("Disk ID is %s\n",Calc.DiskID().c_str());
	printf("URL is %s\n",Calc.SubmitURL().c_str());
}


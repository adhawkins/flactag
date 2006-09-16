#ifndef _DISKID_CALCULATE_H
#define _DISKID_CALCULATE_H

#include <string>

#include "Cuesheet.h"

class CDiskIDCalculate
{
public:
	CDiskIDCalculate(const CCuesheet& Cuesheet);
	
	std::string DiskID() const;
	std::string SubmitURL() const;
	
private:
	std::string m_DiskID;
	CCuesheet m_Cuesheet;
};

#endif

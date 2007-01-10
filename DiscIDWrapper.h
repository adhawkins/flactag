#ifndef _DISCID_WRAPPER_H
#define _DISCID_WRAPPER_H

#include <discid/discid.h>

#include <string>
#include <vector>

class CDiscIDWrapper
{
	public:
		CDiscIDWrapper();
		~CDiscIDWrapper();
		
		bool FromDevice(const std::string& Device);
		bool FromTOC(int First, int Last, int Leadout, std::vector<int> Offsets);
			
		std::string ID() const;
		std::string SubmitURL() const;
		std::string Error() const;
				
	private:
		DiscId *m_DiscID;
};

#endif

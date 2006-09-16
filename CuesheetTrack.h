#ifndef _CUESHEET_TRACK_H
#define _CUESHEET_TRACK_H

#include <FLAC++/metadata.h>

class CCuesheetTrack
{
public:
	CCuesheetTrack(FLAC__byte Number=255, FLAC__uint64 Offset=(FLAC__uint64)-1);

	FLAC__byte Number() const;
	FLAC__uint64 Offset() const;
		
private:
	FLAC__byte m_Number;
	FLAC__uint64 m_Offset;
};

#endif

#include "CuesheetTrack.h"

CCuesheetTrack::CCuesheetTrack(FLAC__byte Number, FLAC__uint64 Offset)
:	m_Number(Number),
	m_Offset(Offset)
{
}

FLAC__byte CCuesheetTrack::Number() const
{
	return m_Number;
}

FLAC__uint64 CCuesheetTrack::Offset() const
{
	return m_Offset;
}

		

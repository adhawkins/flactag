#include "CuesheetTrack.h"

CCuesheetTrack::CCuesheetTrack(int Number, int Offset)
:	m_Number(Number),
	m_Offset(Offset)
{
}

int CCuesheetTrack::Number() const
{
	return m_Number;
}

int CCuesheetTrack::Offset() const
{
	return m_Offset;
}

		

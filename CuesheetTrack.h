#ifndef _CUESHEET_TRACK_H
#define _CUESHEET_TRACK_H

class CCuesheetTrack
{
public:
	CCuesheetTrack(int Number=-1, int Offset=-1);

	int Number() const;
	int Offset() const;
		
private:
	int m_Number;
	int m_Offset;
};

#endif

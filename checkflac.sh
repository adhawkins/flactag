#!/bin/sh

CDROM=/dev/hdc

if [ $# = "1" ]
then
	FILENAME="$1"
	
	CDID=`discid $CDROM`
	FLACID=`flactag --discid $FILENAME | cut -d':' -f 2| cut -d' ' -f 2`

	if [ "$FLACID" != "$CDID" ]
	then
		echo "**********"
		echo "**********"
		echo "**********"
		echo "********** Disc ID of FLAC doesn't match Disc ID of CD  **********"
		echo "********** Please re-rip this CD and remove any invalid **********"
		echo "********** disc IDs from the MusicBrainz service        **********"
		echo "**********"
		echo "**********"
		echo "**********"
	else
		echo "IDs match, disk is OK"
	fi
else
	echo "Usage: $0 flacfile"
fi



#!/bin/sh

CDROM=/dev/hdc

if [ $# = "1" ]
then
	FILENAME="$1"
	
	CDID=`./discid $CDROM`
	FLACID=`./flactag --discid "$FILENAME"`

	if [ "$FLACID" != "$CDID" ]
	then
		echo "**********"
		echo "**********"
		echo "**********"
		echo "********** Disc ID of FLAC doesn't match Disc ID of CD **********"
		echo "**********"
		echo "**********"
		echo "**********"
	else
		echo "IDs match, processing"
		./flactag --write --rename "$FILENAME"
	fi
else
	echo "Usage: $0 flacfile"
fi



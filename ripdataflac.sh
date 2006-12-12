#!/bin/sh

CDROM=/dev/hdc

if [ $# = "2" ]
then

	FILENAME=$1
	SPAN=$2
	
	CDID=`discid $CDROM`
	if cdparanoia $SPAN $FILENAME.bin
	then
		echo "Edit the CUE file to remove the data track"
		sleep 10
		$EDITOR $FILENAME.cue
		if nice flac --replay-gain --endian=big --sign=signed --channels=2 --bps=16 --sample-rate=44100 --cuesheet=$FILENAME.cue $FILENAME.bin
		then
			rm -f $FILENAME.bin
			rm -f ${FILENAME}-fixed.toc
			rm -f $FILENAME.toc
			rm -f $FILENAME.cue*
	
			FLACID=`flactag --discid $FILENAME.flac`
	
			if [ "$FLACID" != "$CDID" ]
			then
				echo "**********"
				echo "**********"
				echo "**********"
				echo "********** Disc ID of FLAC doesn't match Disc ID of CD **********"
				echo "**********"
				echo "**********"
				echo "**********"
			fi
		fi
	fi
else
	echo "Usage: $0 cdname tracks"
fi



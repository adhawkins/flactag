#!/bin/sh

CDROM=/dev/hdc

if [ $1 ]
then

	FILENAME="$1-`date +"%Y-%m-%d.%H:%M:%S"`-$$"
	#cdrdao read-cd --device $CDROM --driver generic-mmc --with-cddb --datafile $FILENAME.bin $FILENAME.toc
	cdrdao read-cd --device $CDROM --driver generic-mmc --datafile $FILENAME.bin $FILENAME.toc
	sed -f tocfix.sed $FILENAME.toc > ${FILENAME}-fixed.toc
	cueconvert ${FILENAME}-fixed.toc $FILENAME.cue
	if nice flac --replay-gain --endian=big --sign=signed --channels=2 --bps=16 --sample-rate=44100 --cuesheet=$FILENAME.cue $FILENAME.bin
	then
		rm -f $FILENAME.bin
		rm -f ${FILENAME}-fixed.toc
		rm -f $FILENAME.toc
		rm -f $FILENAME.cue

		CDID=`./discid $CDROM`
		FLACID=`./flactag --discid $FILENAME.flac`

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
else
	echo "Usage: $0 cdname"
fi



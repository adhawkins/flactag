#!/bin/bash

if [ "$#" -eq "3" ]
then
	USERNAME=$1
	RELEASE=$2
	FILE=$3

	scp flactag.html $USERNAME@web.sourceforge.net:/home/project-web/flactag/htdocs/index.html
	ssh $USERNAME,flactag@shell.sourceforge.net create
	ssh $USERNAME,flactag@shell.sourceforge.net mkdir /home/frs/project/flactag/v$RELEASE
	ssh $USERNAME,flactag@shell.sourceforge.net shutdown
	scp $3 $USERNAME@frs.sourceforge.net://home/frs/project/flactag/v$RELEASE
else
	echo "Usage: $0 username releasenumber /path/to/releasearchive"
	echo
	echo "e.g. $0 adhawkins 2.0.1 /tmp/flactag-2.0.1.tar.gz"
fi


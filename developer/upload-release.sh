#!/bin/bash

USERNAME=$1
RELEASE=$2
FILE=$3

scp flactag.html $USERNAME@web.sourceforge.net:/home/project-web/flactag/htdocs/index.html
ssh $USERNAME,flactag@shell.sourceforge.net create
ssh $USERNAME,flactag@shell.sourceforge.net mkdir /home/frs/project/flactag/v$RELEASE
ssh $USERNAME,flactag@shell.sourceforge.net shutdown
scp $3 $USERNAME@frs.sourceforge.net://home/frs/project/flactag/v$RELEASE

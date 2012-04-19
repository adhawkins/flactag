#!/bin/bash

DoIt()
{
	echo "Entering work directory"
	cd $WORKDIR || return 1

	echo "Cloning repository"
	git clone --quiet git://flactag.git.sourceforge.net/gitroot/flactag/flactag . || return 1

	echo "Setting remote push URL"
	git remote set-url origin --push ssh://$USER@flactag.git.sourceforge.net/gitroot/flactag/flactag || return 1

	#Use for testing script - just push to a local repository
	rm -rf $SRCDIR/../flactag.git-local
	git init --bare $SRCDIR/../flactag.git-local
	git remote set-url origin --push $SRCDIR/../flactag.git-local || return 1

	echo "Making tarball"
	autoreconf --install >/dev/null || return 1
	./configure > /dev/null || return 1
	make dist-gzip >/dev/null || return 1
	[ -f $TARBALL ] || return 1

	echo "Copying tarball to $EXTRACTDIR"
	cp $TARBALL $EXTRACTDIR || return 1

	echo "Entering extract directory"
	cd $EXTRACTDIR || return 1

	echo "Extracting tarball"
	tar xzf $TARBALL || return 1

	echo "Building"
	cd flactag-$VERSION || return 1
	./configure > /dev/null || return 1
	make $MAKEARGS > /dev/null || return 1

	echo "Version test"
	./flactag --version || return 1

	echo "Install test"
	mkdir "$EXTRACTDIR/install-test" | return 1
	make DESTDIR="$EXTRACTDIR/install-test" install > /dev/null || return 1

	echo "Installed binary test"
	ldd "$EXTRACTDIR/install-test/usr/local/bin/flactag" > /dev/null || return 1

	MD5=`md5sum $WORKDIR/$TARBALL | cut -d' ' -f1`
	SHA224=`sha224sum $WORKDIR/$TARBALL | cut -d' ' -f1`

	MAILTEXT="New release of flactag $VERSION is attached:\n\nMD5: $MD5\nSHA224: $SHA224"

	if [ "$TAGANDPUSH" -eq "1" ]
	then
		echo "Tagging work repository"

		cd $WORKDIR
		git tag -s -u $KEYID -m "Tag release $VERSION" -m "MD5 checksum: $MD5" -m "SHA224 checksum $SHA224" $TAGNAME || return 1

		COMMIT=`git show $TAGNAME | grep commit | cut -d ' ' -f 2`

		echo "Pushing new tag to origin"
		git push origin --tags || return 1

		MAILTEXT="$MAILTEXT\nCOMMIT: $COMMIT\n"

		if ! echo -e "$MAILTEXT" | mutt -s "flactag release" -a $TARBALL -- $KEYID
		then
			(echo -e "$MAILTEXT"; uuencode $TARBALL $TARBALL) | Mail -s "flactag release" $KEYID
		fi

		git --no-pager show --raw $TAGNAME

		echo
	fi

	echo -e "$MAILTEXT"
	return 0
}

VALIDARGS=0
TAGANDPUSH=0

if [ "$#" -eq "3" -o "$#" -eq "4" ]
then
	VALIDARGS=1

	#rm -rf /tmp/tmp.*

	if [ "$#" -eq "4" ]
	then
		if [ "x$4" = "x--tag-and-push" ]
		then
			TAGANDPUSH=1
		else
			VALIDARGS="0"
		fi
	fi
fi

if [ "$VALIDARGS" -eq "1" ]
then
	USER="$1"
	VERSION="$2"
	KEYID="$3"

	SRCDIR=`pwd`
	TAGNAME="test-$VERSION"
	TARBALL="flactag-$VERSION.tar.gz"
	#TAGNAME=$VERSION

	WORKDIR=`mktemp -d`
	EXTRACTDIR=`mktemp -d`

	echo "Using directories $WORKDIR and $EXTRACTDIR"

	DoIt
	RET=$?

	if [ "$RET" -eq "1" -o "$TAGANDPUSH" -eq "1" ]
	then
		rm -rf $WORKDIR
	else
		echo "Files remain in $WORKDIR"
	fi

	rm -rf $EXTRACTDIR
else
	echo "Usage: $0 username version keyid [ --tag-and-push ]"
fi

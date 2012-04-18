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
	autoreconf --install 2>/dev/null >/dev/null || return 1
	./configure > /dev/null || return 1
	make dist-gzip 2>/dev/null >/dev/null || return 1
	[ -f flactag-$VERSION.tar.gz ] || return 1

	echo "Copying tarball to $EXTRACTDIR"
	cp flactag-$VERSION.tar.gz $EXTRACTDIR || return 1

	echo "Entering extract directory"
	cd $EXTRACTDIR || return 1

	echo "Extracting tarball"
	tar xf flactag-$VERSION.tar.gz || return 1

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
	ldd "$EXTRACTDIR/install-test/usr/local/bin/flactag" || return 1

	echo "Taking copy of tarball"
	cp $WORKDIR/flactag-$VERSION.tar.gz $SRCDIR || return 1
	MD5=`md5sum $WORKDIR/flactag-$VERSION.tar.gz | cut -d' ' -f1`
	SHA224=`sha224sum $WORKDIR/flactag-$VERSION.tar.gz | cut -d' ' -f1`

	echo "Tagging work repository"

	cd $WORKDIR
	git tag -s -u $KEYID -m "Tag release $VERSION" -m "MD5 checksum: $MD5" -m "SHA224 checksum $SHA224" $TAGNAME || exit 1

	COMMIT=`git show $TAGNAME | grep commit | cut -d ' ' -f 2`

	echo "Pushing new tag to origin"
	git push origin --tags

	MAILTEXT="This is a test mail:\n\nMD5: $MD5\nSHA224: $SHA224\nCOMMIT: $COMMIT\n"

	if ! echo -e "$MAILTEXT" | mutt -s "flactag release" -a flactag-$VERSION.tar.gz -- $KEYID
	then
		(echo -e "$MAILTEXT"; uuencode flactag-$VERSION.tar.gz flactag-$VERSION.tar.gz) | Mail -s "flactag release" $KEYID
	fi

	echo -e "$MAILTEXT"
}

if [ "$#" -eq "3" ]
then
	#rm -rf /tmp/tmp.*

	USER="$1"
	VERSION="$2"
	TAGNAME="test-$VERSION"
	#TAGNAME=$VERSION

	KEYID="$3"
	SRCDIR=`pwd`

	WORKDIR=`mktemp -d`
	EXTRACTDIR=`mktemp -d`

	echo "Using directories $WORKDIR and $EXTRACTDIR"

	DoIt

	rm -rf $WORKDIR
	rm -rf $EXTRACTDIR
else
	echo "Usage: $0 username version keyid"
fi

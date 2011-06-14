AUTOMAKE_OPTIONS = foreign dist-tarZ
ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = checkflac COPYING debian flactag.1.txt flactag.jpg flactag.txt Makefile.raw ripdataflac ripflac tocfix.sed
dist-hook:
	rm -rf `find $(distdir) -name .svn`

#SUBDIRS = MusicBrainz

AM_CFLAGS = -DSYSCONFDIR='"$(sysconfdir)"' -DPKGLIBDIR='"$(pkglibdir)"' 
AM_CFLAGS += `neon-config --cflags`
#-I$(builddir)/lib +=

# used by both binaries:
AM_LDFLAGS = -ldiscid

bin_PROGRAMS = flactag discid
flactag_LDADD = `neon-config --libs` -lslang -lmusicbrainz3 -lFLAC++ -lunac -ljpeg
#discid_LDADD = 



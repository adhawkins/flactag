AUTOMAKE_OPTIONS = foreign dist-tarZ
ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = checkflac COPYING debian flactag.1.txt flactag.jpg flactag.txt Makefile.raw ripdataflac ripflac tocfix.sed
dist-hook:
	rm -rf `find $(distdir) -name .svn`

#SUBDIRS = MusicBrainz

AM_CXXFLAGS = -DSYSCONFDIR='"$(sysconfdir)"' -DPKGLIBDIR='"$(pkglibdir)"' 
AM_CXXFLAGS += `neon-config --cflags`
#-I$(builddir)/lib +=

# used by both binaries:
AM_LDFLAGS = -ldiscid

bin_PROGRAMS = flactag discid
NEON_LIBS = -lneon
flactag_LDADD = $(NEON_LIBS) -lslang -lmusicbrainz3 -lFLAC++ -lunac -ljpeg
#flactag_CFLAGS = -I/usr/include/neon
flactag_SOURCES = flactag.cc Album.cc Track.cc AlbumWindow.cc TrackWindow.cc FlacInfo.cc TagName.cc TagsWindow.cc CuesheetTrack.cc Cuesheet.cc DiscIDWrapper.cc base64.cc ScrollableWindow.cc ConfigFile.cc MusicBrainzInfo.cc FileNameBuilder.cc ErrorLog.cc CommandLine.cc CoverArt.cc UTF8Tag.cc WriteInfo.cc HTTPFetch.cc
#discid_LDADD = 
discid_SOURCES = discid.cc DiscIDWrapper.cc Cuesheet.cc CuesheetTrack.cc



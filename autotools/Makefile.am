AUTOMAKE_OPTIONS = foreign dist-tarZ
ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = COPYING flactag.1.txt flactag.txt flactag.jpg \
	ripflac.in \
	debian

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

dist_bin_SCRIPTS = ripdataflac checkflac
bin_SCRIPTS = ripflac

flactagdatadir = $(datadir)/flactag
dist_flactagdata_DATA = tocfix.sed

ripflac_subst = sed -e "s!INSTALLPATH!$(flactagdatadir)!"

# it is better to process ripflac.in from the Makefile than by adding
# ripflac.in to AC_CONFIG_FILES, because this method should ensure that
# variables are fully resolved (like libexecdir)
ripflac:	ripflac.in Makefile
	$(ripflac_subst) < $(srcdir)/ripflac.in > ripflac
	chmod +x ripflac

man1_MANS = flactag.1

flactag.1:	flactag.1.xml Makefile
	xmlto man flactag.1.xml

flactag.1.xml:	flactag.1.txt Makefile
	asciidoc -d manpage -b docbook flactag.1.txt


CLEANFILES = ripflac flactag.1.xml flactag.1

install-data-hook:
	$(LN_S) $(DESTDIR)$(man1dir)/flactag.1 $(DESTDIR)$(man1dir)/ripflac.1
	$(LN_S) $(DESTDIR)$(man1dir)/flactag.1 \
		$(DESTDIR)$(man1dir)/ripdataflac.1
	$(LN_S) $(DESTDIR)$(man1dir)/flactag.1 $(DESTDIR)$(man1dir)/checkflac.1
	$(LN_S) $(DESTDIR)$(man1dir)/flactag.1 $(DESTDIR)$(man1dir)/discid.1


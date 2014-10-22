AUTOMAKE_OPTIONS = foreign dist-tarZ
ACLOCAL_AMFLAGS = -I m4

man_MANS = flactag.1

EXTRA_DIST = COPYING flactag.1.txt flactag.txt flactag.jpg flactag.html
EXTRA_DIST += ripflac.in
EXTRA_DIST += $(man_MANS)

dist-hook:
	rm -rf `find $(distdir) -name .svn`

#SUBDIRS = MusicBrainz

AM_CPPFLAGS = -DSYSCONFDIR='"$(sysconfdir)"' -DPKGLIBDIR='"$(pkglibdir)"'
AM_CPPFLAGS += @DEP_ALL_CFLAGS@ @DEP_FLACTAG_CFLAGS@
#-I$(builddir)/lib +=

# used by both binaries:
#AM_LDFLAGS = -ldiscid

bin_PROGRAMS = flactag discid
flactag_LDADD = @DEP_ALL_LIBS@ @DEP_FLACTAG_LIBS@
#flactag_CFLAGS = -I/usr/include/neon
flactag_SOURCES = flactag.cc Album.cc Track.cc AlbumWindow.cc TrackWindow.cc FlacInfo.cc TagName.cc TagsWindow.cc CuesheetTrack.cc Cuesheet.cc DiscIDWrapper.cc base64.cc ScrollableWindow.cc ConfigFile.cc MusicBrainzInfo.cc FileNameBuilder.cc ErrorLog.cc CommandLine.cc CoverArt.cc UTF8Tag.cc WriteInfo.cc CoverArtFetch.cc
discid_LDADD = @DEP_ALL_LIBS@
discid_SOURCES = discid.cc DiscIDWrapper.cc Cuesheet.cc CuesheetTrack.cc

dist_bin_SCRIPTS = ripdataflac checkflac
bin_SCRIPTS = ripflac

flactagdatadir = $(datadir)/flactag
dist_flactagdata_DATA = tocfix.sed

doc_DATA = flactag.html

ripflac_subst = sed -e "s!INSTALLPATH!$(flactagdatadir)!"

# it is better to process ripflac.in from the Makefile than by adding
# ripflac.in to AC_CONFIG_FILES, because this method should ensure that
# variables are fully resolved (like libexecdir)
ripflac:	ripflac.in Makefile
	$(ripflac_subst) < $(srcdir)/ripflac.in > ripflac
	chmod +x ripflac

flactag.1:	flactag.1.txt Makefile
	a2x -f manpage flactag.1.txt

flactag.html:	flactag.txt Makefile
	asciidoc -a numbered flactag.txt

CLEANFILES = ripflac flactag.1.xml flactag.1 flactag.html

install-data-hook:
	$(LN_S) $(DESTDIR)$(man1dir)/flactag.1 $(DESTDIR)$(man1dir)/ripflac.1
	$(LN_S) $(DESTDIR)$(man1dir)/flactag.1 \
		$(DESTDIR)$(man1dir)/ripdataflac.1
	$(LN_S) $(DESTDIR)$(man1dir)/flactag.1 $(DESTDIR)$(man1dir)/checkflac.1
	$(LN_S) $(DESTDIR)$(man1dir)/flactag.1 $(DESTDIR)$(man1dir)/discid.1

RM_F = rm -f
uninstall-hook:
	$(RM_F) $(DESTDIR)$(man1dir)/ripflac.1
	$(RM_F) $(DESTDIR)$(man1dir)/ripdataflac.1
	$(RM_F) $(DESTDIR)$(man1dir)/checkflac.1
	$(RM_F) $(DESTDIR)$(man1dir)/discid.1

noinst_HEADERS = CuesheetTrack.h \
        TagName.h \
        WriteInfo.h \
        DiscIDWrapper.h \
        AlbumWindow.h \
        flactag.h \
        base64.h \
        Track.h \
        Album.h \
        ScrollableWindow.h \
        MusicBrainzInfo.h \
        TagsWindow.h \
        CommandLine.h \
        ConfigFile.h \
        FlacInfo.h \
        FileNameBuilder.h \
        UTF8Tag.h \
        TrackWindow.h \
        CoverArt.h \
        ErrorLog.h \
        Cuesheet.h


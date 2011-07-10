INSTALLROOT=/
INSTALLPATH=$(DESTDIR)/$(INSTALLROOT)

VERSION=2.0alpha1

CXXFLAGS=-Wall -Werror -DVERSION=\"${VERSION}\" `neon-config --cflags`
CXXFLAGS+=-g -ggdb -O0
# To enable tracing into the libraries and also expose some more
# obscure bugs during development:
#CXXFLAGS+=-D_GLIBCXX_DEBUG

FLACTAGOBJS=flactag.o Album.o Track.o AlbumWindow.o TrackWindow.o FlacInfo.o \
						TagName.o TagsWindow.o CuesheetTrack.o Cuesheet.o DiscIDWrapper.o \
						base64.o ScrollableWindow.o ConfigFile.o MusicBrainzInfo.o \
						FileNameBuilder.o ErrorLog.o CommandLine.o CoverArt.o UTF8Tag.o \
						WriteInfo.o

DISCIDOBJS=discid.o DiscIDWrapper.o Cuesheet.o CuesheetTrack.o

SRCS=$(FLACTAGOBJS:.o=.cc) $(DISCIDOBJS:.o=.cc)

all: flactag discid flactag.html flactag.1

debian-orig: .phony
	debuild clean
	make dist
	cp flactag-$(VERSION).tar.gz ../flactag_$(VERSION).orig.tar.gz

debian: .phony
	debuild clean
	debuild

repository: debian
	mkdir -p /auto/gently-sw/debian/dists/stable/main/binary-i386 /auto/gently-sw/debian/dists/stable/main/source
	cp ../flactag_$(VERSION)*.deb /auto/gently-sw/debian/dists/stable/main/binary-i386
	cp ../flactag_$(VERSION).orig.tar.gz ../flactag_$(VERSION)*.diff.gz ../flactag_$(VERSION)*.dsc /auto/gently-sw/debian/dists/stable/main/source
	cd /auto/gently-sw/debian/ && \
		dpkg-scansources dists/stable/main/source/ /dev/null | gzip -9c > dists/stable/main/source/Sources.gz && \
		dpkg-scanpackages dists/stable/main/binary-i386 /dev/null | gzip -9c > dists/stable/main/binary-i386/Packages.gz

install: all
	mkdir -p $(INSTALLPATH)/usr/bin
	mkdir -p $(INSTALLPATH)/usr/share/man/man1
	mkdir -p $(INSTALLPATH)/var/lib/flactag
	install -m 755 flactag $(INSTALLPATH)/usr/bin
	install -m 755 discid $(INSTALLPATH)/usr/bin
	install -m 644 tocfix.sed $(INSTALLPATH)/var/lib/flactag
	install -m 755 ripdataflac $(INSTALLPATH)/usr/bin
	install -m 755 checkflac $(INSTALLPATH)/usr/bin
	cat flactag.1 | gzip -9 > $(INSTALLPATH)/usr/share/man/man1/flactag.1.gz
	chmod 644 $(INSTALLPATH)/usr/share/man/man1/flactag.1.gz
	ln -sf flactag.1.gz $(INSTALLPATH)/usr/share/man/man1/ripflac.1.gz
	ln -sf flactag.1.gz $(INSTALLPATH)/usr/share/man/man1/ripdataflac.1.gz
	ln -sf flactag.1.gz $(INSTALLPATH)/usr/share/man/man1/checkflac.1.gz
	ln -sf flactag.1.gz $(INSTALLPATH)/usr/share/man/man1/discid.1.gz
	sed -e "s#\(.*\)INSTALLPATH\(.*\)#\1$(INSTALLROOT)/var/lib/flactag\2#" ripflac > $(INSTALLPATH)/usr/bin/ripflac
	chmod 755 ${INSTALLPATH}/usr/bin/ripflac

flactag.1: flactag.1.xml Makefile
	xmlto man flactag.1.xml

flactag.1.xml: flactag.1.txt Makefile
	asciidoc -d manpage -b docbook flactag.1.txt

flactag.html: flactag.txt Makefile
	asciidoc -a numbered flactag.txt

clean:
	rm -f $(FLACTAGOBJS) $(DISCIDOBJS) flactag.html *.d *.bak *~ *.tar.gz flactag discid flactag.man svn-commit.* flactag.1.xml flactag.1.html flactag.1

flactag-$(VERSION).tar.gz: dist

dist: all
	svn update && \
		mkdir -p flactag-$(VERSION) && \
		cp flactag.jpg *.cc *.h Makefile flactag.txt flactag.1.txt flactag.html COPYING ripflac ripdataflac checkflac tocfix.sed flactag-$(VERSION) && \
		tar zcf flactag-$(VERSION).tar.gz flactag-$(VERSION) && \
		rm -rf flactag-$(VERSION)

install-webpages: flactag-$(VERSION).tar.gz flactag.html
	mkdir -p /auto/gently-sw/flactag-1.1
	cp flactag.html /auto/gently-sw/flactag-1.1/index.html
	cp flactag.html flactag.jpg /auto/gently-sw/flactag-1.1/
	cp flactag-$(VERSION).tar.gz  /auto/gently-sw/flactag-1.1

%.d: %.cc
	@echo DEPEND $< $@
	@$(CXX) -MM $(CXXFLAGS) $< | \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

flactag: $(FLACTAGOBJS)
	g++ `neon-config --libs` -o $@ -lslang -ldiscid -lFLAC++ -lunac -ljpeg -lmusicbrainz4 $(FLACTAGOBJS)

discid: $(DISCIDOBJS)
	g++ -o $@ -ldiscid $^

ifneq "$(MAKECMDGOALS)" "clean"
-include $(SRCS:.cc=.d)
endif

.phony:

INSTALLROOT=/usr
INSTALLPATH=$(DESTDIR)/$(INSTALLROOT)

VERSION=1.1-RC1

CXXFLAGS=-Wall -Werror -DVERSION=\"${VERSION}\"

FLACTAGOBJS=flactag.o Album.o Track.o AlbumWindow.o TrackWindow.o FlacInfo.o \
						TagName.o TagsWindow.o CuesheetTrack.o Cuesheet.o DiscIDWrapper.o \
						base64.o ScrollableWindow.o ConfigFile.o MusicBrainzInfo.o \
						FileNameBuilder.o ErrorLog.o CommandLine.o CoverArt.o UTF8Tag.o \
						WriteInfo.o
						
DISCIDOBJS=discid.o DiscIDWrapper.o Cuesheet.o CuesheetTrack.o

SRCS=$(FLACTAGOBJS:.o=.cc) $(DISCIDOBJS:.o=.cc) 

all: flactag discid flactag.html

install: all
	mkdir -p $(INSTALLPATH)/bin
	install -m 755 flactag $(INSTALLPATH)/bin
	install -m 755 discid $(INSTALLPATH)/bin
	install -m 755 tocfix.sed $(INSTALLPATH)/bin
	install -m 755 ripdataflac.sh $(INSTALLPATH)/bin
	install -m 755 checkflac.sh $(INSTALLPATH)/bin
	sed -e "s#\(.*\)INSTALLPATH\(.*\)#\1$(INSTALLROOT)/bin\2#" ripflac.sh > $(INSTALLPATH)/bin/ripflac.sh
	chmod 755 ${INSTALLPATH}/bin/ripflac.sh
	
flactag.html: flactag.txt Makefile
	asciidoc -a numbered flactag.txt
	
clean:
	rm -f $(FLACTAGOBJS) $(DISCIDOBJS) flactag.html *.d *.bak *~ *.tar.gz flactag discid flactag.man

flactag-$(VERSION).tar.gz: dist

dist: all
	svn update && \
		mkdir -p flactag-$(VERSION) && \
		cp *.cc *.h Makefile flactag.txt flactag.html COPYING ripflac.sh ripdataflac.sh checkflac.sh tocfix.sed flactag-$(VERSION) && \
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
	g++ -o $@ -lslang -lmusicbrainz3 -ldiscid -lFLAC++ -lhttp_fetcher -lunac -ljpeg $^
	
discid: $(DISCIDOBJS)
	g++ -o $@ -ldiscid $^
	
include $(SRCS:.cc=.d)

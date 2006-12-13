INSTALLPATH=/usr/local

VERSION=1.0RC2

CXXFLAGS=-Wall -Werror -DVERSION=\"${VERSION}\"

FLACTAGOBJS=flactag.o Album.o Track.o AlbumWindow.o TrackWindow.o FlacInfo.o \
						TagName.o TagsWindow.o CuesheetTrack.o Cuesheet.o DiskIDCalculate.o \
						sha1.o base64.o ScrollableWindow.o ConfigFile.o MusicBrainzInfo.o \
						FileNameBuilder.o ErrorLog.o CommandLine.o CoverArt.o UTF8Tag.o
						
DISCIDOBJS=discid.o

SRCS=$(FLACTAGOBJS:.o=.cc) $(DISCIDOBJS:.o=.cc) 

all: flactag discid flactag.html

install: all
	mkdir -p $(INSTALLPATH)/bin
	install -m 755 flactag $(INSTALLPATH)/bin
	install -m 755 discid $(INSTALLPATH)/bin
	install -m 755 tocfix.sed $(INSTALLPATH)/bin
	install -m 755 ripdataflac.sh $(INSTALLPATH)/bin
	install -m 755 checkflac.sh $(INSTALLPATH)/bin
	sed -e "s#\(.*\)INSTALLPATH\(.*\)#\1$(INSTALLPATH)/bin\2#" ripflac.sh > $(INSTALLPATH)/bin/ripflac.sh
	chmod 755 ${INSTALLPATH}/bin/ripflac.sh
	
flactag.html: flactag.txt Makefile
	asciidoc -a numbered flactag.txt
	
clean:
	rm -f $(FLACTAGOBJS) $(DISCIDOBJS) flactag.html *.d *.bak *~ *.tar.gz flactag discid flactag.man

flactag-$(VERSION).tar.gz: all
	svn update && cd .. && tar zcf flactag/flactag-$(VERSION).tar.gz \
							flactag/*.cc flactag/*.h flactag/Makefile flactag/flactag.txt \
							flactag/flactag.html flactag/flactag.sgml flactag/COPYING \
							flactag/ripflac.sh flactag/ripdataflac.sh flactag/checkflac.sh \
							flactag/fixtoc.sed

install-webpages: flactag-$(VERSION).tar.gz flactag.html
	mkdir -p /auto/gentlyweb/flactag
	cp flactag.html /auto/gentlyweb/flactag/index.html
	cp flactag.html /auto/gentlyweb/flactag/
	cp flactag-$(VERSION).tar.gz  /auto/gentlyweb/flactag
	
%.d: %.cc
	@echo DEPEND $< $@
	@$(CXX) -MM $(CXXFLAGS) $< | \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

flactag: $(FLACTAGOBJS)
	g++ -o $@ -lslang -lmusicbrainz -lFLAC++ -lhttp_fetcher -lunac $^
	
discid: $(DISCIDOBJS)
	g++ -o $@ -lmusicbrainz $^
	
include $(SRCS:.cc=.d)

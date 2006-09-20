VERSION=0.03

CXXFLAGS=-Wall -Werror

FLACTAGOBJS=flactag.o Album.o Track.o AlbumWindow.o TrackWindow.o FlacInfo.o \
						TagName.o TagsWindow.o CuesheetTrack.o Cuesheet.o DiskIDCalculate.o \
						sha1.o base64.o ScrollableWindow.o ConfigFile.o MusicBrainzInfo.cc
						
DISCIDOBJS=discid.o

SRCS=$(FLACTAGOBJS:.o=.cc) $(DISCIDOBJS:.o=.cc) 

all: flactag discid flactag.txt flactag.html

flactag.txt: flactag.sgml Makefile
	sgml2txt --pass="-P-bc" --blanks=1 flactag.sgml
	
flactag.html: flactag.sgml Makefile
	sgml2html --split=0 --toc=1 flactag.sgml
	
clean:
	rm -f $(FLACTAGOBJS) $(DISCIDOBJS) flactag.txt flactag.html *.d *.bak *~ *.tar.gz flactag discid

flactag-$(VERSION).tar.gz: all
	cd .. && tar zcf flactag/flactag-$(VERSION).tar.gz flactag/*.cc flactag/*.h flactag/Makefile flactag/flactag.txt flactag/flactag.html flactag/flactag.sgml

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
	g++ -o $@ -lslang -lmusicbrainz -lFLAC++ $^
	
discid: $(DISCIDOBJS)
	g++ -o $@ -lmusicbrainz $^
	
include $(SRCS:.cc=.d)

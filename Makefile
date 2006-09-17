VERSION=0.01

CXXFLAGS=-Wall -Werror

FLACTAGOBJS=flactag.o Album.o Track.o AlbumWindow.o TrackWindow.o FlacInfo.o \
						TagName.o TagsWindow.o CuesheetTrack.o Cuesheet.o DiskIDCalculate.o \
						sha1.o base64.o
						
DISCIDOBJS=discid.o

SRCS=$(FLACTAGOBJS:.o=.cc) $(DISCIDOBJS:.o=.cc) 

all: flactag discid flactag.txt flactag.html

flactag.txt: flactag.sgml
	sgml2txt --pass="-P-bc" --blanks=1 flactag.sgml
	
flactag.html: flactag.sgml
	sgml2html --split=0 flactag.sgml
	
clean:
	rm -f $(FLACTAGOBJS) $(DISCIDOBJS) flactag.txt flactag.html *.d *.bak *~ *.tar.gz flactag discid

flactag-$(VERSION).tar.gz: all
	cd .. && tar zcf flactag/flactag-$(VERSION).tar.gz flactag/*.cc flactag/*.h flactag/Makefile flactag/flactag.txt flactag/flactag.html flactag/flactag.sgml

install-webpages: flactag-$(VERSION).tar.gz index.html
	mkdir -p /auto/gentlyweb/flactag
	cp flactag.html flactag-$(VERSION).tar.gz /auto/gentlyweb/flactag/index.html
	
%.d: %.cc
	@echo DEPEND $< $@
	@$(CXX) -MM $(CXXFLAGS) $< | \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

flactag: $(FLACTAGOBJS)
	g++ -o $@ -lslang -lmusicbrainz -lFLAC++ $^
	
discid: $(DISCIDOBJS)
	g++ -o $@ -lmusicbrainz $^
	
include $(SRCS:.cc=.d)

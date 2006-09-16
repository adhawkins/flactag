VERSION=0.01

CXXFLAGS=-Wall -Werror

FLACTAGOBJS=flactag.o Album.o Track.o AlbumWindow.o TrackWindow.o FlacInfo.o \
						TagName.o TagsWindow.o CuesheetTrack.o Cuesheet.o DiskIDCalculate.o \
						sha1.o base64.o
						
DISCIDOBJS=discid.o

SRCS=$(FLACTAGOBJS:.o=.cc) $(DISCIDOBJS:.o=.cc) 

all: flactag discid

clean:
	rm -f $(FLACTAGOBJS) $(DISCIDOBJS) *.d *.bak *~ *.tar.gz flactag discid

flactag-$(VERSION).tar.gz: all
	cd .. && tar zcf flactag/flactag-$(VERSION).tar.gz flactag/*.cc flactag/*.h flactag/Makefile flactag/README.txt

install-webpages: flactag-$(VERSION).tar.gz
	mkdir -p /auto/gentlyweb/flactag
	cp index.html flactag-$(VERSION).tar.gz /auto/gentlyweb/flactag
	
%.d: %.cc
	@echo DEPEND $< $@
	@$(CXX) -MM $(CXXFLAGS) $< | \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

flactag: $(FLACTAGOBJS)
	g++ -o $@ -lslang -lmusicbrainz -lFLAC++ $^
	
discid: $(DISCIDOBJS)
	g++ -o $@ -lmusicbrainz $^
	
include $(SRCS:.cc=.d)

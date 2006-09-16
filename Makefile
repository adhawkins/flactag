VERSION=0.01

CXXFLAGS=-Wall -Werror

FLACTAGOBJS=flactag.o Album.o Track.o AlbumWindow.o TrackWindow.o FlacInfo.o \
						TagName.o TagsWindow.o CuesheetTrack.o Cuesheet.o DiskIDCalculate.o \
						sha1.o base64.o
						
DISCIDOBJS=discid.o

SRCS=$(FLACTAGOBJS:.o=.cc) $(DISCIDOBJS:.o=.cc) 

all: flactag discid

clean:
	rm -f $(FLACTAGOBJS) $(DISCIDOBJS) *.d *.bak *~ *.tar.bz2 flactag discid

distrib:
	cd .. && tar cf - flactag/*.cc flactag/*.h flactag/Makefile flactag/README.txt | bzip2 > flactag/flactag-$(VERSION).tar.bz2
		
%.d: %.cc
	@echo DEPEND $< $@
	@$(CXX) -MM $(CXXFLAGS) $< | \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

flactag: $(FLACTAGOBJS)
	g++ -o $@ -lslang -lmusicbrainz -lFLAC++ $^
	
discid: $(DISCIDOBJS)
	g++ -o $@ -lmusicbrainz $^
	
include $(SRCS:.cc=.d)

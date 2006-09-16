FLACTAGOBJS=flactag.o Album.o Track.o AlbumWindow.o TrackWindow.o FlacInfo.o \
						TagName.o TagsWindow.o CuesheetTrack.o Cuesheet.o DiskIDCalculate.o \
						sha1.o base64.o
						
DISCIDOBJS=discid.o

SHAOBJS=shatest.o sha1.o base64.o

SUBMITURLOBJS=submiturl.o FlacInfo.o Cuesheet.o CuesheetTrack.o DiskIDCalculate.o \
						TagName.o sha1.o base64.o

SRCS=$(FLACTAGOBJS:.o=.cc) $(DISCIDOBJS:.o=.cc) $(SHAOBJS:.o=.cc) $(SUBMITURLOBJS:.o=.cc)

all: flactag discid shatest submiturl

clean:
	rm -f $(FLACTAGOBJS) $(DISCIDOBJS) $(SHAOBJS) $(SUBMITURLOBJS) *.d *.bak *~ flactag discid shatest submiturl 
	
%.d: %.cc
	@echo DEPEND $< $@
	@$(CXX) -MM $(CXXFLAGS) $< | \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

flactag: $(FLACTAGOBJS)
	g++ -o $@ -lslang -lmusicbrainz -lFLAC++ $^
	
discid: $(DISCIDOBJS)
	g++ -o $@ -lmusicbrainz $^
	
shatest: $(SHAOBJS)
	g++ -o $@ -lmusicbrainz $^
	
submiturl: $(SUBMITURLOBJS)
	g++ -o $@ -lFLAC++ -lmusicbrainz $^
	
include $(SRCS:.cc=.d)

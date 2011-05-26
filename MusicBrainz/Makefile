CPPSRCS=xmlParser/xmlParser.cpp
CCSRCS=MusicBrainz-adh.cc HTTPFetch.cc ReleaseList.cc Release.cc
PROGSRCS=mbtest.cc

OBJS=$(CPPSRCS:.cpp=.o) $(CCSRCS:.cc=.o) $(PROGSRCS:.cc=.o)
PROGS=$(PROGSRCS:.cc=)

LIB=libmusicbrainz-adh.so

LD=g++
CXXFLAGS=-Wall -Werror `neon-config --cflags` -DVERSION=\"1.0\"

all: $(PROGS) $(LIB)

$(LIB):  $(OBJS) $(CCOBJS)
	$(LD) -shared `neon-config --libs` -o $@ $^

mbtest: mbtest.o $(LIB)
	$(LD) -lmusicbrainz-adh -L. -o $@ mbtest.o
	
clean:
	rm -f $(OBJS) $(CCOBJS) $(LIB) $(PROGS)


%.d: %.cc
	@echo DEPEND $< $@
	@$(CXX) -MM $(CXXFLAGS) $< | \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

%.d: %.cpp
	@echo DEPEND $< $@
	@$(CXX) -MM $(CXXFLAGS) $< | \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

include $(CPPSRCS:.cpp=.d) $(CCSRCS:.cc=.d) $(PROGSRCS:.cc=.d)

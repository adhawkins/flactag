CPPSRCS=xmlParser/xmlParser.cpp
CCSRCS=MusicBrainz-adh.cc HTTPFetch.cc ReleaseList.cc Release.cc TextRepresentation.cc RelationList.cc \
	Relation.cc LabelInfoList.cc LabelInfo.cc Label.cc ArtistCredit.cc NameCredit.cc Artist.cc ReleaseGroup.cc
	
PROGSRCS=mbtest.cc

OBJS=$(CPPSRCS:.cpp=.o) $(CCSRCS:.cc=.o) $(PROGSRCS:.cc=.o)
PROGS=$(PROGSRCS:.cc=)

LIB=libmusicbrainz-adh.so

LD=g++
CXXFLAGS=-Wall -Werror -Wextra -pedantic-errors `neon-config --cflags` -DVERSION=\"1.0\" 
#CXXFLAGS+=-g -ggdb
# To enable tracing into the libraries and also expose some more
# obscure bugs during development:
#CXXFLAGS+=-D_GLIBCXX_DEBUG

all: $(PROGS) $(LIB)

$(LIB):  $(OBJS) $(CCOBJS)
	$(LD) -shared `neon-config --libs` -o $@ $^

mbtest: mbtest.o $(LIB)
	$(LD) -lmusicbrainz-adh -L. -o $@ mbtest.o
	
clean:
	rm -f $(OBJS) $(CCOBJS) $(LIB) $(PROGS) *.d


%.d: %.cc
	@echo DEPEND $< $@
	@$(CXX) -MM $(CXXFLAGS) $< | \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

%.d: %.cpp
	@echo DEPEND $< $@
	@$(CXX) -MM $(CXXFLAGS) $< | \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

include $(CPPSRCS:.cpp=.d) $(CCSRCS:.cc=.d) $(PROGSRCS:.cc=.d)

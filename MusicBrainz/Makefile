CPPSRCS=xmlParser/xmlParser.cpp
CCSRCS=Alias.cc Annotation.cc Artist.cc ArtistCredit.cc Attribute.cc CDStub.cc Collection.cc \
				Disc.cc FreeDBDisc.cc HTTPFetch.cc ISRC.cc Label.cc LabelInfo.cc Lifespan.cc \
				ListTest.cc Medium.cc Metadata.cc MusicBrainz-adh.cc NameCredit.cc NoneMBTrack.cc \
				PUID.cc Rating.cc Recording.cc Relation.cc Release.cc ReleaseGroup.cc Tag.cc \
				TextRepresentation.cc Track.cc UserRating.cc UserTag.cc Work.cc
	
PROGSRCS=mbtest.cc

OBJS=$(CPPSRCS:.cpp=.o) $(CCSRCS:.cc=.o) $(PROGSRCS:.cc=.o)
PROGS=$(PROGSRCS:.cc=)

LIB=libmusicbrainz-adh.a

LD=g++
CXXFLAGS=-Wall -Werror -Wextra -pedantic-errors `neon-config --cflags` -DVERSION=\"1.0\" 
#CXXFLAGS+=-g -ggdb
# To enable tracing into the libraries and also expose some more
# obscure bugs during development:
#CXXFLAGS+=-D_GLIBCXX_DEBUG

all: $(PROGS) $(LIB)

$(LIB):  $(OBJS) $(CCOBJS)
	$(AR) rcs $@ $^

mbtest: mbtest.o $(LIB)
	$(LD) -o $@ mbtest.o $(LIB) `neon-config --libs`
	
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

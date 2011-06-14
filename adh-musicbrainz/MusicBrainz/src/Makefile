CPPSRCS=xmlParser.cpp
CCSRCS=Alias.cc Annotation.cc Artist.cc ArtistCredit.cc Attribute.cc CDStub.cc Collection.cc \
				Disc.cc FreeDBDisc.cc HTTPFetch.cc ISRC.cc Label.cc LabelInfo.cc Lifespan.cc \
				Medium.cc Metadata.cc NameCredit.cc NoneMBTrack.cc \
				PUID.cc Query.cc Rating.cc Recording.cc Relation.cc Release.cc ReleaseGroup.cc Tag.cc \
				TextRepresentation.cc Track.cc UserRating.cc UserTag.cc Work.cc

PROGSRCS=mbtest.cc ListTest.cc

OBJS=$(CPPSRCS:.cpp=.o) $(CCSRCS:.cc=.o)
PROGOBJS=$(PROGSRCS:.cc=.o)
PROGS=$(PROGSRCS:.cc=)

LIB=libmusicbrainz4.so

LD=g++
CXXFLAGS=-Wall -Werror -Wextra -pedantic-errors `neon-config --cflags` -DVERSION=\"1.0\" -I../include -I.
CXXFLAGS+=-g -ggdb -O0
# To enable tracing into the libraries and also expose some more
# obscure bugs during development:
CXXFLAGS+=-D_GLIBCXX_DEBUG

all: $(PROGS) $(LIB)

$(LIB):  $(OBJS) $(CCOBJS)
	$(LD) -shared -o $@ $^

mbtest: mbtest.o $(LIB)
	$(LD) -o $@ mbtest.o `neon-config --libs` -L. -lmusicbrainz4

ListTest: ListTest.o $(LIB)
	$(LD) -o $@ ListTest.o `neon-config --libs` -L. -lmusicbrainz4

clean:
	rm -f $(OBJS) $(PROGOBJS) $(CCOBJS) $(LIB) $(PROGS) *.d


%.d: %.cc
	@echo DEPEND $< $@
	@$(CXX) -MM $(CXXFLAGS) $< | \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

%.d: %.cpp
	@echo DEPEND $< $@
	@$(CXX) -MM $(CXXFLAGS) $< | \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

ifneq "$(MAKECMDGOALS)" "clean"
-include $(CPPSRCS:.cpp=.d) $(CCSRCS:.cc=.d) $(PROGSRCS:.cc=.d)
endif

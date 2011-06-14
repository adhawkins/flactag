all: src

src: .phony
	$(MAKE) -C src

clean: .phony
	rm -rf libmusicbrainz4
	$(MAKE) -C src clean

dist: clean
	mkdir libmusicbrainz4
	cp -r Makefile src include libmusicbrainz4 && tar cf - --exclude "\.svn" libmusicbrainz4 | gzip -9 > libmusicbrainz4.tar.gz

.phony:

all:
	for DIR in ${SUBDIR}; do \
		$(MAKE) -C $$DIR -f Makefile.bsd-wrapper; \
		if [ $$? -ne 0 ]; then \
			break; \
		fi \
	done

install:
	for DIR in ${SUBDIR}; do \
		$(MAKE) -C $$DIR -f Makefile.bsd-wrapper DESTDIR="${DESTDIR}" install; \
		if [ $$? -ne 0 ]; then \
			break; \
		fi \
	done

clean:
	for DIR in ${SUBDIR}; do \
		$(MAKE) -C $$DIR -f Makefile.bsd-wrapper clean; \
		if [ $$? -ne 0 ]; then \
			break; \
		fi \
	done

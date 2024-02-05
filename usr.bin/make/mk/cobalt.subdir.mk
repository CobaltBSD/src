all:
	for DIR in ${SUBDIR}; do \
		$(MAKE) -C $$DIR; \
		if [ $$? -ne 0 ]; then \
			break; \
		fi \
	done

install:
	for DIR in ${SUBDIR}; do \
		$(MAKE) -C $$DIR DESTDIR="${DESTDIR}" install; \
		if [ $$? -ne 0 ]; then \
			break; \
		fi \
	done

clean:
	for DIR in ${SUBDIR}; do \
		$(MAKE) -C $$DIR clean; \
		if [ $$? -ne 0 ]; then \
			break; \
		fi \
	done

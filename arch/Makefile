SUBARCH = x86

.PHONY: clean

clean:
	@for d in $(SUBARCH); \
	do \
		${MAKE} -C $$d clean; \
	done


TOPDIR = $(shell pwd)

DIRS = linked_list stack

all:
	list='$(DIRS)'; for subdir in $$list; do \
	$(MAKE) -C $$subdir all; \
	done;

clean:
	list='$(DIRS)'; for subdir in $$list; do \
	$(MAKE) -C $$subdir clean; \
	done;

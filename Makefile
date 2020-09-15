
TOPDIR = $(shell pwd)

DIRS = utilities linked_list stack queue binary_tree sort

all:
	list='$(DIRS)'; for subdir in $$list; do \
	$(MAKE) -C $$subdir all; \
	done;

clean:
	list='$(DIRS)'; for subdir in $$list; do \
	$(MAKE) -C $$subdir clean; \
	done;

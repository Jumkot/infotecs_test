SUBDIRS = lib prog1 prog2

all:
	@for dir in $(SUBDIRS); do \
	  $(MAKE) -C $$dir; \
	done

run1:
	@$(MAKE) -C prog1 run

run2:
	@$(MAKE) -C prog2 run

clean:
	@for dir in $(SUBDIRS); do \
	  $(MAKE) -C $$dir clean; \
	done

.PHONY: all run1 run2 clean
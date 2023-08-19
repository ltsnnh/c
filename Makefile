###############################################################################
# Top Level
###############################################################################

TOPDIR  := $(realpath $(CURDIR))

.PHONY: clean clobber
clean:
	-rm -f $(TOPDIR)/*/*/*/*.o

clobber: clean
	-rm -f $(TOPDIR)/*/*/main

# End

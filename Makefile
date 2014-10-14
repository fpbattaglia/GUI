export CANOPY_PREFIX
export CANOPY_INCLUDES
export CANOPY_LIBS

all:
	cd Builds/Linux && $(MAKE) 

clean showvars:
	cd Builds/Linux && $(MAKE) $@

.PHONY: all clean showvars

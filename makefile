# tranche/makefile
# sharing and installing are broken (this file comes from another project)

SHELL=/bin/bash

-include makefile-flags

.PHONY: all 
all: version

.PHONY: dep
dep:
	if [ -e $(DEPFILE) ]; then rm $(DEPFILE); fi
	$(MAKE) $@

.PHONY: lib
lib:
	$(MAKE) $@

.PHONY: exec
exec:
	$(MAKE) $@

.PHONY: share
share:
	$(MAKE) $@

.PHONY: clean
clean:
	$(MAKE) $@

.PHONY: dist-clean
dist-clean:
	$(MAKE) $@

%::
	$(MAKE) $@





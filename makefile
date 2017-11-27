
all::
	mkdir -p bin

all clean ::
	$(MAKE) -C myWindows              $@
	$(MAKE) -C 7zip/Bundles/Alone     $@
	
clean::
	find . -name "*~" -exec rm -f {} \;
	rm -fr bin

REP=$(shell pwd)
ARCHIVE=$(shell basename $(REP))

tar2 : clean
	rm -f  $(ARCHIVE)_src.tar.bz2
	cd .. ; (tar cf - $(ARCHIVE) | bzip2 -9 > $(ARCHIVE)_src.tar.bz2)

tar_bin:
	rm -f  $(ARCHIVE)_x86_linux_bin.tar.bz2
	cd .. ; (tar cf - $(ARCHIVE)/bin $(ARCHIVE)/ChangeLog $(ARCHIVE)/html $(ARCHIVE)/DOC $(ARCHIVE)/README $(ARCHIVE)/TODO | bzip2 -9 > $(ARCHIVE)_x86_linux_bin.tar.bz2)


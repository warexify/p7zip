
all::
	mkdir -p bin/Codecs bin/Formats

all clean ::
	$(MAKE) -C myWindows              $@
	$(MAKE) -C 7zip/Bundles/Alone     $@
	$(MAKE) -C 7zip/UI/Console        $@
	$(MAKE) -C 7zip/Archive/7z        $@
	$(MAKE) -C 7zip/Archive/Arj       $@
	$(MAKE) -C 7zip/Archive/BZip2     $@
	$(MAKE) -C 7zip/Archive/Cab       $@
	$(MAKE) -C 7zip/Archive/cpio      $@
	$(MAKE) -C 7zip/Archive/Deb       $@
	$(MAKE) -C 7zip/Archive/GZip      $@
	$(MAKE) -C 7zip/Archive/Rar       $@
	$(MAKE) -C 7zip/Archive/RPM       $@
	$(MAKE) -C 7zip/Archive/Split     $@
	$(MAKE) -C 7zip/Archive/Tar       $@
	$(MAKE) -C 7zip/Archive/Zip       $@
	$(MAKE) -C 7zip/Compress/Branch   $@
	$(MAKE) -C 7zip/Compress/ByteSwap $@
	$(MAKE) -C 7zip/Compress/BZip2    $@
	$(MAKE) -C 7zip/Compress/Copy     $@
	$(MAKE) -C 7zip/Compress/Deflate  $@
	$(MAKE) -C 7zip/Compress/Implode  $@
	$(MAKE) -C 7zip/Compress/LZMA     $@
	$(MAKE) -C 7zip/Compress/PPMD     $@
	$(MAKE) -C 7zip/Crypto/7zAES      $@
	$(MAKE) -C 7zip/Crypto/AES        $@
	
clean::
	rm -f *~
	rm -fr bin

REP=$(shell pwd)
ARCHIVE=$(shell basename $(REP))

tar2 : clean
	rm -f  $(ARCHIVE).tar.bz2
	cd .. ; (tar cf - $(ARCHIVE) | bzip2 -9 > $(ARCHIVE).tar.bz2)

tar_bin:
	tar cf - bin html LGPL.txt README TODO | bzip2 -9 > ../p7zip_bin.tar.bz2



.PHONY: all 7za sfx 7z common clean tar_src tar_bin

all::7za

all2: 7za sfx 7z

common:
	mkdir -p  bin
	$(MAKE) -C BUILD/Common           all
	$(MAKE) -C myWindows              all

7za: common
	$(MAKE) -C 7zip/Bundles/Alone     all

sfx: common
	mkdir -p  bin
	$(MAKE) -C 7zip/Bundles/SFXCon    all

7z: common
	mkdir -p  bin/Codecs bin/Formats
	$(MAKE) -C 7zip/UI/Console        all
	$(MAKE) -C 7zip/Archive/7z        all
	$(MAKE) -C 7zip/Archive/Arj       all
	$(MAKE) -C 7zip/Archive/BZip2     all
	$(MAKE) -C 7zip/Archive/GZip      all
	$(MAKE) -C 7zip/Archive/Split     all
	$(MAKE) -C 7zip/Archive/Tar       all
	$(MAKE) -C 7zip/Archive/Zip       all
	$(MAKE) -C 7zip/Compress/Branch   all
	$(MAKE) -C 7zip/Compress/BZip2    all
	$(MAKE) -C 7zip/Compress/Copy     all
	$(MAKE) -C 7zip/Compress/Deflate  all
	$(MAKE) -C 7zip/Compress/Implode  all
	$(MAKE) -C 7zip/Compress/LZMA     all
	$(MAKE) -C 7zip/Compress/PPMD     all
	$(MAKE) -C 7zip/Crypto/7zAES      all
	$(MAKE) -C 7zip/Crypto/AES        all
	$(MAKE) -C 7zip/Archive/Cab       all
	$(MAKE) -C 7zip/Archive/Cpio      all
	$(MAKE) -C 7zip/Archive/Deb       all
	$(MAKE) -C 7zip/Archive/Rar       all
	$(MAKE) -C 7zip/Archive/RPM       all
	$(MAKE) -C 7zip/Compress/ByteSwap all

clean:
	$(MAKE) -C BUILD/Common           clean
	$(MAKE) -C myWindows              clean
	$(MAKE) -C 7zip/Bundles/Alone     clean
	$(MAKE) -C 7zip/Bundles/SFXCon    clean
	$(MAKE) -C 7zip/UI/Console        clean
	$(MAKE) -C 7zip/Archive/7z        clean
	$(MAKE) -C 7zip/Archive/Arj       clean
	$(MAKE) -C 7zip/Archive/BZip2     clean
	$(MAKE) -C 7zip/Archive/GZip      clean
	$(MAKE) -C 7zip/Archive/Split     clean
	$(MAKE) -C 7zip/Archive/Tar       clean
	$(MAKE) -C 7zip/Archive/Zip       clean
	$(MAKE) -C 7zip/Compress/Branch   clean
	$(MAKE) -C 7zip/Compress/BZip2    clean
	$(MAKE) -C 7zip/Compress/Copy     clean
	$(MAKE) -C 7zip/Compress/Deflate  clean
	$(MAKE) -C 7zip/Compress/Implode  clean
	$(MAKE) -C 7zip/Compress/LZMA     clean
	$(MAKE) -C 7zip/Compress/PPMD     clean
	$(MAKE) -C 7zip/Crypto/7zAES      clean
	$(MAKE) -C 7zip/Crypto/AES        clean
	$(MAKE) -C 7zip/Archive/Cab       clean
	$(MAKE) -C 7zip/Archive/Cpio      clean
	$(MAKE) -C 7zip/Archive/Deb       clean
	$(MAKE) -C 7zip/Archive/Rar       clean
	$(MAKE) -C 7zip/Archive/RPM       clean
	$(MAKE) -C 7zip/Compress/ByteSwap clean
	find . -name "*~" -exec rm -f {} \;
	rm -fr bin

REP=$(shell pwd)
ARCHIVE=$(shell basename $(REP))

tar_src : clean
	rm -f  $(ARCHIVE)_src.tar.bz2
	cd .. ; (tar cf - $(ARCHIVE) | bzip2 -9 > $(ARCHIVE)_src.tar.bz2)

tar_bin:
	rm -f  $(ARCHIVE)_x86_linux_bin.tar.bz2
	cd .. ; (tar cf - $(ARCHIVE)/bin $(ARCHIVE)/contrib $(ARCHIVE)/ChangeLog $(ARCHIVE)/DOCS $(ARCHIVE)/README $(ARCHIVE)/TODO | bzip2 -9 > $(ARCHIVE)_x86_linux_bin.tar.bz2)


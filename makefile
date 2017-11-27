
DEST_BIN=/usr/local/bin
DEST_SHARE=/usr/local/lib/p7zip

.PHONY: all 7za sfx 7z common clean tar_src tar_bin

all::7za

all2: 7za sfx 7z

common:
	mkdir -p  bin
	cd BUILD/Common ; $(MAKE) all
	cd myWindows    ; $(MAKE) all

7za: common
	cd 7zip/Bundles/Alone ; $(MAKE) all

sfx: common
	mkdir -p  bin
	cd 7zip/Bundles/SFXCon ; $(MAKE) all

7z: common
	mkdir -p  bin/Codecs bin/Formats
	cd 7zip/UI/Console        ; $(MAKE) all
	cd 7zip/Archive/7z        ; $(MAKE) all
	cd 7zip/Archive/Arj       ; $(MAKE) all
	cd 7zip/Archive/BZip2     ; $(MAKE) all
	cd 7zip/Archive/GZip      ; $(MAKE) all
	cd 7zip/Archive/Split     ; $(MAKE) all
	cd 7zip/Archive/Tar       ; $(MAKE) all
	cd 7zip/Archive/Zip       ; $(MAKE) all
	cd 7zip/Compress/Branch   ; $(MAKE) all
	cd 7zip/Compress/BZip2    ; $(MAKE) all
	cd 7zip/Compress/Copy     ; $(MAKE) all
	cd 7zip/Compress/Deflate  ; $(MAKE) all
	cd 7zip/Compress/Implode  ; $(MAKE) all
	cd 7zip/Compress/LZMA     ; $(MAKE) all
	cd 7zip/Compress/PPMD     ; $(MAKE) all
	cd 7zip/Crypto/7zAES      ; $(MAKE) all
	cd 7zip/Crypto/AES        ; $(MAKE) all
	cd 7zip/Archive/Cab       ; $(MAKE) all
	cd 7zip/Archive/Cpio      ; $(MAKE) all
	cd 7zip/Archive/Deb       ; $(MAKE) all
	cd 7zip/Archive/Rar       ; $(MAKE) all
	cd 7zip/Archive/RPM       ; $(MAKE) all
	cd 7zip/Compress/ByteSwap ; $(MAKE) all

clean:
	cd BUILD/Common           ; $(MAKE) clean
	cd myWindows              ; $(MAKE) clean
	cd 7zip/Bundles/Alone     ; $(MAKE) clean
	cd 7zip/Bundles/SFXCon    ; $(MAKE) clean
	cd 7zip/UI/Console        ; $(MAKE) clean
	cd 7zip/Archive/7z        ; $(MAKE) clean
	cd 7zip/Archive/Arj       ; $(MAKE) clean
	cd 7zip/Archive/BZip2     ; $(MAKE) clean
	cd 7zip/Archive/GZip      ; $(MAKE) clean
	cd 7zip/Archive/Split     ; $(MAKE) clean
	cd 7zip/Archive/Tar       ; $(MAKE) clean
	cd 7zip/Archive/Zip       ; $(MAKE) clean
	cd 7zip/Compress/Branch   ; $(MAKE) clean
	cd 7zip/Compress/BZip2    ; $(MAKE) clean
	cd 7zip/Compress/Copy     ; $(MAKE) clean
	cd 7zip/Compress/Deflate  ; $(MAKE) clean
	cd 7zip/Compress/Implode  ; $(MAKE) clean
	cd 7zip/Compress/LZMA     ; $(MAKE) clean
	cd 7zip/Compress/PPMD     ; $(MAKE) clean
	cd 7zip/Crypto/7zAES      ; $(MAKE) clean
	cd 7zip/Crypto/AES        ; $(MAKE) clean
	cd 7zip/Archive/Cab       ; $(MAKE) clean
	cd 7zip/Archive/Cpio      ; $(MAKE) clean
	cd 7zip/Archive/Deb       ; $(MAKE) clean
	cd 7zip/Archive/Rar       ; $(MAKE) clean
	cd 7zip/Archive/RPM       ; $(MAKE) clean
	cd 7zip/Compress/ByteSwap ; $(MAKE) clean
	find . -name "*~" -exec rm -f {} \;
	rm -fr bin

install:
	./install.sh $(DEST_BIN) $(DEST_SHARE)

REP=$(shell pwd)
ARCHIVE=$(shell basename $(REP))

tar_src : clean
	rm -f  ../$(ARCHIVE)_src.tar.bz2
	chmod +x install.sh contrib/VirtualFileSystemForMidnightCommander/u7z
	cd .. ; (tar cf - $(ARCHIVE) | bzip2 -9 > $(ARCHIVE)_src.tar.bz2)

tar_bin:
	rm -f  ../$(ARCHIVE)_x86_linux_bin.tar.bz2
	chmod +x install.sh contrib/VirtualFileSystemForMidnightCommander/u7z
	cd .. ; (tar cf - $(ARCHIVE)/bin $(ARCHIVE)/contrib $(ARCHIVE)/install.sh $(ARCHIVE)/ChangeLog $(ARCHIVE)/DOCS $(ARCHIVE)/README $(ARCHIVE)/TODO | bzip2 -9 > $(ARCHIVE)_x86_linux_bin.tar.bz2)


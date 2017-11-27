
.SUFFIXES: .cpp

VPATH=7zip/Crypto/7zAES \
	7zip/Crypto/AES \
	7zip/Crypto/Zip \
	Common \
	7zip/UI/Common \
	7zip/Compress/BZip2 \
	7zip/Archive/BZip2 \
	7zip/Archive/Common \
	7zip/Archive/7z \
	7zip/Archive/Tar \
	7zip/Archive/GZip \
	7zip/Archive/Zip \
	7zip/UI/Console \
	7zip/Compress/Copy \
	Windows \
	7zip/Compress/Deflate \
	7zip/Common \
	7zip/Compress/BZip2/Original \
	7zip/Compress/Huffman \
	7zip/Compress/Implode \
	7zip/Compress/LZ \
	7zip/Compress/LZMA \
	7zip/Compress/LZ/MT \
	7zip/Compress/PPMD \
	7zip/Compress/RangeCoder \
	7zip/Compress/Branch \
	myWindows

#   -DUNICODE -D_UNICODE
DEFINES=-D_FILE_OFFSET_BITS=64 -DENV_UNIX -DNDEBUG -D_CONSOLE \
-DEXCLUDE_COM -DNO_REGISTRY \
-DFORMAT_7Z -DFORMAT_BZIP2 -DFORMAT_ZIP -DFORMAT_TAR \
-DFORMAT_GZIP -DCOMPRESS_LZMA -DCOMPRESS_BCJ_X86 -DCOMPRESS_BCJ2 \
-DCOMPRESS_COPY -DCOMPRESS_MF_PAT -DCOMPRESS_MF_BT -DCOMPRESS_MF_HC \
-DCOMPRESS_MF_MT -DCOMPRESS_PPMD -DCOMPRESS_DEFLATE -DCOMPRESS_DEFLATE64 \
-DCOMPRESS_IMPLODE -DCOMPRESS_BZIP2 -DCRYPTO_ZIP -DCRYPTO_7ZAES -DCRYPTO_AES 

CPPFLAGS=-I. -I7zip -I7zip/Bundles/Alone -ImyWindows -Iinclude_windows $(DEFINES)

CC=gcc  -s -O2
CXX=g++ -s -O2

# NewHandler.o
OBJ=\
7zAES.o 7zCompressionMode.o 7zDecode.o 7zEncode.o 7zExtract.o 7zFolderInStream.o \
7zFolderOutStream.o 7zHandler.o 7zHandlerOut.o 7zHeader.o 7zIn.o 7zMethodID.o 7zOut.o \
7zProperties.o 7zSpecStream.o 7zUpdate.o AlignedBuffer.o ArchiverInfo.o BZip2Decoder.o \
BZip2Encoder.o BZip2Error.o BZip2Handler.o BZip2HandlerOut.o BZip2Update.o CRC.o \
CoderMixer.o CoderMixer2.o ConsoleClose.o CopyCoder.o CrossThreadProgress.o \
DefaultName.o DeflateDecoder.o DeflateEncoder.o DummyOutStream.o EnumDirItems.o \
Error.o Extract.o ExtractCallback.o ExtractingFilePath.o FileDir.o FileFind.o FileIO.o \
FileName.o FilePathAutoRename.o FileStreams.o GZipHandler.o GZipHandlerOut.o GZipHeader.o \
GZipIn.o GZipOut.o GZipUpdate.o HuffmanEncoder.o ImplodeDecoder.o ImplodeHuffmanDecoder.o InBuffer.o \
InOutTempBuffer.o InStreamWithCRC.o IntToString.o ItemNameUtils.o LSBFDecoder.o LSBFEncoder.o LZInWindow.o \
LZMADecoder.o LZMAEncoder.o LZMALen.o LZMALiteral.o LZOutWindow.o LimitedStreams.o List.o ListFileUtils.o \
MT.o Main.o MainAr.o MultiStream.o MyAES.o OffsetStream.o OpenArchive.o OpenCallback.o \
OutBuffer.o OutStreamWithCRC.o PPMDDecoder.o PPMDEncoder.o PercentPrinter.o ProgressUtils.o \
PropIDUtils.o PropVariant.o PropVariantConversions.o Random.o RangeCoderBit.o SHA256.o \
SortUtils.o StreamBinder.o StreamObjects.o String.o \
StringConvert.o StringToInt.o Synchronization.o TarHandler.o TarHandlerOut.o TarHeader.o \
TarIn.o TarOut.o TarUpdate.o TempFiles.o UTFConvert.o Update.o UpdateAction.o UpdateCallback.o UpdatePair.o \
UpdateProduce.o UserInputUtils.o Vector.o Wildcard.o ZipCipher.o ZipCrypto.o \
ZipHandler.o ZipHandlerOut.o ZipHeader.o ZipIn.o ZipItem.o ZipOut.o ZipUpdate.o ZipAddCommon.o \
aescrypt.o aeskey.o \
aestab.o blocksort.o bzlib.o compress.o crctable.o decompress.o huffman.o randtable.o x86.o x86_2.o \
 StdOutStream.o StdInStream.o CommandLineParser.o

MY_WINDOWS=myEvents.o myFiles.o myFindFile.o myOther.o \
     wine_wsprintf.o wine_date_and_time.o wine_BSTR.o wine_variant.o wine_strings.o \
     stuff_for_cygwin.o

REP=$(shell pwd)
ARCHIVE=$(shell basename $(REP))
LIBS=-lpthread

all: test_emul 7z

test_emul : test_emul.o $(MY_WINDOWS) String.o StringConvert.o
	$(CXX) $(CPPFLAGS) -pedantic -Wall $^ -o $@ $(LIBS)

7z :  $(OBJ) $(MY_WINDOWS)
	$(CXX) $^ -o $@  $(LIBS) 

.cpp.o :
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

# really odd : VPATH is not enough (Cygwin only)
%.o : 7zip/Archive/Zip/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

# $(CXX) $(CPPFLAGS) -E $< > $@.i

TarHandler.o : 7zip/Archive/Tar/TarHandler.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

TarHandlerOut.o : 7zip/Archive/Tar/TarHandlerOut.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

TarHeader.o : 7zip/Archive/Tar/TarHeader.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

TarIn.o : 7zip/Archive/Tar/TarIn.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

TarOut.o : 7zip/Archive/Tar/TarOut.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

TarUpdate.o : 7zip/Archive/Tar/TarUpdate.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

clean:
	rm -f 7z *.exe *.o *.i *.bak *~
	rm -f */*~ */*/*~ */*/*/*~ 
	rm -f core a.out a.exe
	rm -f out.txt out2.txt
	rm -f test_emul test_emul.exe
	rm -f toto toto.7z debug


tar2 : clean
	rm -f  $(ARCHIVE).tar.bz2
	cd .. ; (tar cf - $(ARCHIVE) | bzip2 -9 > $(ARCHIVE).tar.bz2)


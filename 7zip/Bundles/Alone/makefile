
PROG=../../../bin/7za

LOCAL_FLAGS=-DENV_UNIX \
-DEXCLUDE_COM -DNO_REGISTRY -DFORMAT_7Z -DFORMAT_BZIP2 -DFORMAT_ZIP \
-DFORMAT_TAR -DFORMAT_GZIP -DCOMPRESS_LZMA -DCOMPRESS_BCJ_X86 \
-DCOMPRESS_BCJ2 -DCOMPRESS_COPY -DCOMPRESS_MF_MT -DCOMPRESS_PPMD \
-DCOMPRESS_DEFLATE -DCOMPRESS_DEFLATE64 -DCOMPRESS_IMPLODE -DCOMPRESS_BZIP2 \
-DCRYPTO_ZIP -DCRYPTO_7ZAES -DCRYPTO_AES \
-I../../../myWindows \
-I../../../ \
-I../../../include_windows


include ../../../makefile.machine

MY_WINDOWS= \
	$(MY_HOME)/myEvents.o \
	$(MY_HOME)/myDirectoryAndPath.o \
	$(MY_HOME)/myGetTickCount.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/wine_date_and_time.o \
	$(MY_HOME)/myFindFile.o \
	$(MY_HOME)/myFiles.o \
	$(MY_HOME)/myModuleFileName.o \
	$(MY_HOME)/my_itow.o \
	$(MY_HOME)/stuff_for_cygwin.o

OBJS=\
MyWindows.o \
7zAES.o \
7zCompressionMode.o \
7zDecode.o \
7zEncode.o \
7zExtract.o \
7zFolderInStream.o \
7zFolderOutStream.o \
7zHandler.o \
7zHandlerOut.o \
7zHeader.o \
7zIn.o \
7zMethodID.o \
7zOut.o \
7zProperties.o \
7zSpecStream.o \
7zUpdate.o \
AlignedBuffer.o \
Alloc.o \
BZip2Decoder.o \
BZip2Encoder.o \
BZip2Error.o \
BZip2Handler.o \
BZip2HandlerOut.o \
BZip2Update.o \
BranchCoder.o \
CRC.o \
CommandLineParser.o \
ConsoleClose.o \
CopyCoder.o \
DefaultName.o \
DeflateDecoder.o \
DeflateEncoder.o \
DummyOutStream.o \
ExtractingFilePath.o \
FileDir.o \
FileFind.o \
FileName.o \
FilePathAutoRename.o \
FileStreams.o \
FilterCoder.o \
GZipHandler.o \
GZipHandlerOut.o \
GZipHeader.o \
GZipIn.o \
GZipOut.o \
GZipUpdate.o \
HuffmanEncoder.o \
ImplodeDecoder.o \
ImplodeHuffmanDecoder.o \
InBuffer.o \
InStreamWithCRC.o \
IntToString.o \
ItemNameUtils.o \
LSBFDecoder.o \
LSBFEncoder.o \
LZInWindow.o \
LZMADecoder.o \
LZMAEncoder.o \
LZOutWindow.o \
LimitedStreams.o \
List.o \
ListFileUtils.o \
LockedStream.o \
MT.o \
Main.o \
MainAr.o \
MyAES.o \
OffsetStream.o \
OpenCallbackConsole.o \
OutBuffer.o \
OutStreamWithCRC.o \
PPMDDecoder.o \
PPMDEncoder.o \
PercentPrinter.o \
ProgressUtils.o \
PropIDUtils.o \
PropVariant.o \
PropVariantConversions.o \
Random.o \
RangeCoderBit.o \
SHA256.o \
SortUtils.o \
StdInStream.o \
StdOutStream.o \
StreamBinder.o \
StreamObjects.o \
String.o \
StringConvert.o \
StringToInt.o \
Synchronization.o \
System.o \
TarHandler.o \
TarHandlerOut.o \
TarHeader.o \
TarIn.o \
TarOut.o \
TarUpdate.o \
TempFiles.o \
UTFConvert.o \
UpdateAction.o \
UpdateCallbackConsole.o \
UpdatePair.o \
UpdateProduce.o \
UserInputUtils.o \
Vector.o \
Wildcard.o \
ZipAddCommon.o \
ZipCipher.o \
ZipCrypto.o \
ZipHandlerOut.o \
ZipHeader.o \
ZipIn.o \
ZipItem.o \
ZipOut.o \
ZipUpdate.o \
aescrypt.o \
aeskey.o \
aestab.o \
blocksort.o \
bzlib.o \
compress.o \
crctable.o \
decompress.o \
huffman.o \
randtable.o \
x86.o \
x86_2.o \
ArchiveCommandLine.o \
ArchiverInfo.o \
CoderMixer.o \
CoderMixer2.o \
CoderMixer2MT.o \
CrossThreadProgress.o \
EnumDirItems.o \
Extract.o \
InOutTempBuffer.o \
OpenArchive.o \
Error.o \
ArchiveOpenCallback.o \
ExtractCallbackConsole.o \
ArchiveExtractCallback.o \
UpdateCallback.o \
Update.o \
ZipHandler.o \
FileIO.o

include ../../../makefile.glb


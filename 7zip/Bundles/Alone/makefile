PROG=../../../bin/7za

LOCAL_FLAGS=-D_FILE_OFFSET_BITS=64 -DENV_UNIX -DNDEBUG \
-DEXCLUDE_COM -DNO_REGISTRY \
-DFORMAT_7Z -DFORMAT_BZIP2 -DFORMAT_ZIP -DFORMAT_TAR \
-DFORMAT_GZIP -DCOMPRESS_LZMA -DCOMPRESS_BCJ_X86 -DCOMPRESS_BCJ2 \
-DCOMPRESS_COPY -DCOMPRESS_MF_PAT -DCOMPRESS_MF_BT -DCOMPRESS_MF_HC \
-DCOMPRESS_MF_MT -DCOMPRESS_PPMD -DCOMPRESS_DEFLATE -DCOMPRESS_DEFLATE64 \
-DCOMPRESS_IMPLODE -DCOMPRESS_BZIP2 -DCRYPTO_ZIP -DCRYPTO_7ZAES -DCRYPTO_AES

include ../../../makefile.machine

MY_WINDOWS=$(MY_HOME)/myEvents.o \
	$(MY_HOME)/myFiles.o \
	$(MY_HOME)/myFindFile.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/myDirectoryAndPath.o \
	$(MY_HOME)/myModuleFileName.o \
	$(MY_HOME)/wine_wsprintf.o \
	$(MY_HOME)/wine_date_and_time.o \
	$(MY_HOME)/wine_BSTR.o \
	$(MY_HOME)/wine_variant.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/stuff_for_cygwin.o

OBJS=\
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

include ../../../makefile.glb


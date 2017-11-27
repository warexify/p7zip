PROG=../../../bin/Formats/Zip.dll

LOCAL_FLAGS=-DCRYPTO_ZIP

MY_WINDOWS= \
	$(MY_HOME)/wine_date_and_time.o \
	$(MY_HOME)/myModuleFileName.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/myEvents.o \
	$(MY_HOME)/myFindFile.o \
	$(MY_HOME)/myGetTickCount.o \
	$(MY_HOME)/wine_strings.o

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Vector.o\
../../../BUILD/Common/Alloc.o\
../../../BUILD/Common/StringConvert.o\
../../../BUILD/Common/String.o\
../../../BUILD/Common/CRC.o\
../../../BUILD/Common/StringToInt.o\
../../../BUILD/Common/Random.o\
DllExports.o\
DLL.o\
FileFind.o\
PropVariant.o\
Synchronization.o\
CodecsPath.o\
CoderLoader.o\
CrossThreadProgress.o\
FilterCoder.o\
InStreamWithCRC.o\
ItemNameUtils.o\
OutStreamWithCRC.o\
LimitedStreams.o\
OffsetStream.o\
ProgressUtils.o\
StreamBinder.o\
StreamObjects.o\
ZipAddCommon.o\
ZipHandler.o\
ZipHandlerOut.o\
ZipHeader.o\
ZipIn.o\
ZipItem.o\
ZipOut.o\
ZipUpdate.o\
CopyCoder.o\
ZipCipher.o\
ZipCrypto.o\
7zMethodID.o\
7zMethods.o

include ../../../makefile.glb


PROG=../../../bin/Formats/Rar.dll

LOCAL_FLAGS=

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)

MY_WINDOWS=$(MY_HOME)/myEvents.o \
	$(MY_HOME)/myFindFile.o \
	$(MY_HOME)/myModuleFileName.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/wine_date_and_time.o \
	$(MY_HOME)/my_ui64toa.o \
	$(MY_HOME)/wine_strings.o

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Alloc.o\
../../../BUILD/Common/Vector.o\
../../../BUILD/Common/StringConvert.o\
../../../BUILD/Common/String.o\
../../../BUILD/Common/CRC.o\
DllExports.o\
CodecsPath.o\
FilterCoder.o\
InStreamWithCRC.o\
OutStreamWithCRC.o\
DLL.o\
FileFind.o\
PropVariant.o\
Synchronization.o\
CopyCoder.o\
RarHandler.o\
RarHeader.o\
RarIn.o\
RarItem.o\
RarVolumeInStream.o\
RarAES.o\
sha1.o\
Rar20Cipher.o\
Rar20Crypto.o\
LimitedStreams.o\
ProgressUtils.o\
StreamObjects.o\
7zMethodID.o\
7zMethods.o

include ../../../makefile.glb


PROG=../../../bin/Formats/7z.dll

LOCAL_FLAGS=

include ../../../makefile.machine

LOCAL_SHARED=$(LINK_SHARED)
LIBS=$(LOCAL_LIBS_DLL)

MY_WINDOWS= \
	$(MY_HOME)/myEvents.o \
	$(MY_HOME)/myFindFile.o \
	$(MY_HOME)/myFiles.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/myDirectoryAndPath.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/wine_date_and_time.o \
	$(MY_HOME)/myModuleFileName.o \

include ../../../makefile.machine

OBJS = \
../../../BUILD/Common/MyWindows.o \
../../../BUILD/Common/Alloc.o \
../../../BUILD/Common/Vector.o \
../../../BUILD/Common/StringConvert.o \
../../../BUILD/Common/String.o \
../../../BUILD/Common/CRC.o \
../../../BUILD/Common/IntToString.o \
../../../BUILD/Common/StringToInt.o \
DllExports.o \
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
7zMethods.o \
7zOut.o \
7zProperties.o \
7zSpecStream.o \
7zUpdate.o \
CodecsPath.o \
CoderLoader.o \
CoderMixer2.o \
CoderMixer2MT.o \
CrossThreadProgress.o \
FilterCoder.o \
InStreamWithCRC.o \
ItemNameUtils.o \
MultiStream.o \
OutStreamWithCRC.o \
InOutTempBuffer.o \
LimitedStreams.o \
LockedStream.o \
OutBuffer.o \
ProgressUtils.o \
StreamBinder.o \
StreamObjects.o \
DLL.o \
FileDir.o \
FileFind.o \
FileIO.o \
PropVariant.o \
Synchronization.o \
CopyCoder.o

include ../../../makefile.glb


PROG=../../../bin/Formats/7z.dll

LOCAL_FLAGS=

LOCAL_SHARED=-shared

MY_WINDOWS=$(MY_HOME)/wine_BSTR.o \
	$(MY_HOME)/wine_date_and_time.o \
	$(MY_HOME)/wine_variant.o \
	$(MY_HOME)/myDirectoryAndPath.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/myModuleFileName.o \
	$(MY_HOME)/myEvents.o \
	$(MY_HOME)/myFiles.o \
	$(MY_HOME)/myFindFile.o \
	$(MY_HOME)/wine_strings.o

OBJS = \
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
	CRC.o \
	IntToString.o \
	String.o \
	StringConvert.o \
	StringToInt.o \
	Vector.o \
	CodecsPath.o \
	CoderMixer2.o \
	CrossThreadProgress.o \
	InStreamWithCRC.o \
	ItemNameUtils.o \
	OutStreamWithCRC.o \
	InOutTempBuffer.o \
	LimitedStreams.o \
	MultiStream.o \
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


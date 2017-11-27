PROG=../../../bin/Formats/Zip.dll

LOCAL_FLAGS=-DCRYPTO_ZIP

MY_WINDOWS= $(MY_HOME)/wine_variant.o \
	$(MY_HOME)/wine_date_and_time.o \
	$(MY_HOME)/wine_BSTR.o \
	$(MY_HOME)/myModuleFileName.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/myEvents.o \
	$(MY_HOME)/myFindFile.o \
	$(MY_HOME)/wine_strings.o

LOCAL_SHARED=-shared

OBJS = \
	DllExports.o \
	CRC.o \
	Random.o \
	String.o \
	StringConvert.o \
	StringToInt.o \
	Vector.o \
	DLL.o \
	FileFind.o \
	PropVariant.o \
	Synchronization.o \
	CodecsPath.o \
	CoderMixer.o \
	CrossThreadProgress.o \
	InStreamWithCRC.o \
	ItemNameUtils.o \
	OutStreamWithCRC.o \
	LimitedStreams.o \
	OffsetStream.o \
	ProgressUtils.o \
	StreamBinder.o \
	StreamObjects.o \
	ZipAddCommon.o \
	ZipHandler.o \
	ZipHandlerOut.o \
	ZipHeader.o \
	ZipIn.o \
	ZipItem.o \
	ZipOut.o \
	ZipUpdate.o \
	CopyCoder.o \
	ZipCipher.o \
	ZipCrypto.o \
	7zMethods.o

include ../../../makefile.glb


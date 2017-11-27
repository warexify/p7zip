PROG=../../../bin/Formats/Rar.dll

LOCAL_FLAGS=

LOCAL_SHARED=-shared

MY_WINDOWS=$(MY_HOME)/myEvents.o \
	$(MY_HOME)/myFindFile.o \
	$(MY_HOME)/myModuleFileName.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/my_itow.o \
	$(MY_HOME)/wine_BSTR.o \
	$(MY_HOME)/wine_variant.o \
	$(MY_HOME)/wine_date_and_time.o \
	$(MY_HOME)/wine_strings.o

MY_WINDOWS2=wine_BSTR.o wine_date_and_time.o wine_variant.o \
	myModuleFileName.o myOther.o myEvents.o \
	myFiles.o myFindFile.o wine_strings.o

OBJS = \
	DllExports.o \
	CRC.o \
	String.o \
	StringConvert.o \
	Vector.o \
	CodecsPath.o \
	CoderMixer.o \
	CoderMixer2.o \
	CrossThreadProgress.o \
	InStreamWithCRC.o \
	OutStreamWithCRC.o \
	DLL.o \
	FileFind.o \
	PropVariant.o \
	Synchronization.o \
	CopyCoder.o \
	RarHandler.o \
	RarHeader.o \
	RarIn.o \
	RarItem.o \
	RarVolumeInStream.o \
	RarAES.o \
	sha1.o \
	Rar20Cipher.o \
	Rar20Crypto.o \
	LimitedStreams.o \
	ProgressUtils.o \
	StreamBinder.o \
	StreamObjects.o \
	7zMethods.o \

# NewHandler.o

include ../../../makefile.glb


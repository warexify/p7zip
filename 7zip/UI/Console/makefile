PROG=../../../bin/7z

LOCAL_FLAGS=

OPERATING_SYSTEM=$(shell uname -o)

ifeq ($(OPERATING_SYSTEM),Cygwin)
# Cygwin does not support -ldl
LOCAL_LIBS=-lpthread
else
LOCAL_LIBS=-lpthread -ldl -lm
endif

MY_WINDOWS=$(MY_HOME)/myDirectoryAndPath.o \
	$(MY_HOME)/myLastError.o \
	$(MY_HOME)/myEvents.o \
	$(MY_HOME)/myFiles.o \
	$(MY_HOME)/myFindFile.o \
	$(MY_HOME)/myModuleFileName.o \
	$(MY_HOME)/wine_wsprintf.o \
	$(MY_HOME)/wine_date_and_time.o \
	$(MY_HOME)/wine_BSTR.o \
	$(MY_HOME)/wine_variant.o \
	$(MY_HOME)/wine_strings.o \
	$(MY_HOME)/stuff_for_cygwin.o


OBJS = \
	ConsoleClose.o \
	Extract.o \
	ExtractCallback.o \
	List.o \
	Main.o \
	MainAr.o \
	OpenCallback.o \
	PercentPrinter.o \
	TempFiles.o \
	Update.o \
	UpdateCallback.o \
	UserInputUtils.o \
	DLL.o \
	Error.o \
	FileDir.o \
	FileFind.o \
	FileIO.o \
	FileName.o \
	PropVariant.o \
	PropVariantConversions.o \
	CommandLineParser.o \
	IntToString.o \
	ListFileUtils.o \
	StdInStream.o \
	StdOutStream.o \
	String.o \
	StringConvert.o \
	UTFConvert.o \
	Vector.o \
	Wildcard.o \
	ArchiverInfo.o \
	DefaultName.o \
	EnumDirItems.o \
	ExtractingFilePath.o \
	OpenArchive.o \
	PropIDUtils.o \
	SortUtils.o \
	UpdateAction.o \
	UpdatePair.o \
	UpdateProduce.o \
	FilePathAutoRename.o \
	FileStreams.o \
	CopyCoder.o

# Registry.o \
# WorkDir.o \
# NewHandler.o

include ../../../makefile.glb


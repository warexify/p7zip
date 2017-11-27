PROG=../../../bin/Formats/split.dll

LOCAL_FLAGS=

LOCAL_SHARED=-shared

MY_WINDOWS=$(MY_HOME)/wine_variant.o \
	   $(MY_HOME)/wine_BSTR.o \
	   $(MY_HOME)/wine_strings.o \
	   $(MY_HOME)/myLastError.o

OBJS = \
	DllExports.o \
	String.o \
	StringConvert.o \
	Vector.o \
	PropVariant.o \
	CopyCoder.o \
	ProgressUtils.o \
	SplitHandler.o \
	SplitHanlerOut.o

include ../../../makefile.glb


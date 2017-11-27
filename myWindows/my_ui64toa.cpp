#include "StdAfx.h"
#include "myPrivate.h"

#define MAX_STR_ITOW   40
wchar_t * _itow (int val,wchar_t *buf,int radix)
{
	if (radix != 10) throw "_itow : radix not supported";

    char as[MAX_STR_ITOW];
	sprintf(as,"%d",val);
	mbstowcs(buf, as, MAX_STR_ITOW);
	return (buf);
}

char * _ui64toa(unsigned long long int value, char *s, int base)
{
	if (base == 8)
	{
		sprintf(s,"%llo",(unsigned long long)value);
		return s;	
	}

	throw "_ui64toa : not implemented for base != 8";
}


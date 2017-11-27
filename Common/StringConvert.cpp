// Common/StringConvert.cpp

#include "StdAfx.h"

#include "StringConvert.h"

#ifdef WIN32

UString MultiByteToUnicodeString(const AString &srcString, UINT codePage)
{
  UString resultString;
  if(!srcString.IsEmpty())
  {
    int numChars = MultiByteToWideChar(codePage, 0, srcString, 
      srcString.Length(), resultString.GetBuffer(srcString.Length()), 
      srcString.Length() + 1);
    #ifndef _WIN32_WCE
    if(numChars == 0)
      throw 282228;
    #endif
    resultString.ReleaseBuffer(numChars);
  }
  return resultString;
}

AString UnicodeStringToMultiByte(const UString &srcString, UINT codePage)
{
  AString resultString;
  if(!srcString.IsEmpty())
  {
    int numRequiredBytes = srcString.Length() * 2;
    int numChars = WideCharToMultiByte(codePage, 0, srcString, 
      srcString.Length(), resultString.GetBuffer(numRequiredBytes), 
      numRequiredBytes + 1, NULL, NULL);
    #ifndef _WIN32_WCE
    if(numChars == 0)
      throw 282229;
    #endif
    resultString.ReleaseBuffer(numChars);
  }
  return resultString;
}

#ifndef _WIN32_WCE
AString SystemStringToOemString(const CSysString &srcString)
{
  AString result;
  CharToOem(srcString, result.GetBuffer(srcString.Length() * 2));
  result.ReleaseBuffer();
  return result;
}
#endif

#else
/*
UString MultiByteToUnicodeString(const AString &srcString, UINT codePage)
{
  UString resultString;
  for (int i = 0; i < srcString.Length(); i++)
    resultString += wchar_t((unsigned char)(srcString[i]));

  // printf("MultiByteToUnicodeString '%s' -> '%ls'\n",&srcString[0],&resultString[0]);
  return resultString;
}

AString UnicodeStringToMultiByte(const UString &srcString, UINT codePage)
{
  AString resultString;
  for (int i = 0; i < srcString.Length(); i++)
    resultString += (unsigned char)(srcString[i]);

  // printf("UnicodeStringToMultiByte '%ls' -> '%s'\n",&srcString[0],&resultString[0]);

  return resultString;
}
*/

UString MultiByteToUnicodeString(const AString &srcString, UINT /* codePage */ )
{
  UString resultString;
  if(!srcString.IsEmpty())
  {
    int numChars = mbstowcs(resultString.GetBuffer(srcString.Length()),srcString,srcString.Length()+1);
    if (numChars < 0) throw "Your environment does not support UNICODE filenames";
    resultString.ReleaseBuffer(numChars);
  }
  return resultString;
}

AString UnicodeStringToMultiByte(const UString &srcString, UINT /* codePage */ )
{
  AString resultString;
  if(!srcString.IsEmpty())
  {
    int numRequiredBytes = srcString.Length() * 6+1;
    int numChars = wcstombs(resultString.GetBuffer(numRequiredBytes),srcString,numRequiredBytes);
    if (numChars < 0) throw "Your environment does not support UNICODE filenames";
    resultString.ReleaseBuffer(numChars);
  }
  return resultString;
}

#endif

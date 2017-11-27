/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#include <wchar.h>
#include <windows.h>

// #define TRACEN(u) u;
#define TRACEN(u)  /* */

#ifndef __CYGWIN__
#define HAVE_TIMEGM
#endif

#define TICKSPERSEC        10000000
#define TICKSPERMSEC       10000
#define SECSPERDAY         86400
#define SECSPERHOUR        3600
#define SECSPERMIN         60
#define MINSPERHOUR        60
#define HOURSPERDAY        24
#define EPOCHWEEKDAY       1  /* Jan 1, 1601 was Monday */
#define DAYSPERWEEK        7
#define EPOCHYEAR          1601
#define DAYSPERNORMALYEAR  365
#define DAYSPERLEAPYEAR    366
#define MONSPERYEAR        12
#define DAYSPERQUADRICENTENNIUM (365 * 400 + 97)
#define DAYSPERNORMALCENTURY (365 * 100 + 24)
#define DAYSPERNORMALQUADRENNIUM (365 * 4 + 1)

/* 1601 to 1970 is 369 years plus 89 leap days */
#define SECS_1601_TO_1970  ((369 * 365 + 89) * (ULONGLONG)SECSPERDAY)
#define TICKS_1601_TO_1970 (SECS_1601_TO_1970 * TICKSPERSEC)
/* 1601 to 1980 is 379 years plus 91 leap days */
#define SECS_1601_TO_1980  ((379 * 365 + 91) * (ULONGLONG)SECSPERDAY)
#define TICKS_1601_TO_1980 (SECS_1601_TO_1980 * TICKSPERSEC)

static int TIME_GetBias(time_t utc, int *pdaylight) {
  struct tm *ptm;
  static time_t last_utc;
  static int last_bias;
  static int last_daylight;
  int ret;

  if(utc == last_utc) {
    *pdaylight = last_daylight;
    ret = last_bias;
  } else {
    ptm = localtime(&utc);
    *pdaylight = last_daylight = ptm->tm_isdst; /* daylight for local timezone */
    ptm = gmtime(&utc);
    ptm->tm_isdst = *pdaylight; /* use local daylight, not that of Greenwich */
    last_utc = utc;
    ret = last_bias = (int)(utc-mktime(ptm));
  }
  return ret;
}


static void RtlSystemTimeToLocalTime( const LARGE_INTEGER *SystemTime,
                                      PLARGE_INTEGER LocalTime ) {
  int bias, daylight;
  time_t gmt = time(NULL);
  bias = TIME_GetBias(gmt, &daylight);
  LocalTime->QuadPart = SystemTime->QuadPart + bias * (LONGLONG)10000000;
}

void WINAPI RtlSecondsSince1970ToTime( DWORD Seconds, LARGE_INTEGER *Time ) {
  ULONGLONG secs = Seconds * (ULONGLONG)TICKSPERSEC + TICKS_1601_TO_1970;
  Time->u.LowPart  = (DWORD)secs;
  Time->u.HighPart = (DWORD)(secs >> 32);
}


BOOL WINAPI DosDateTimeToFileTime( WORD fatdate, WORD fattime, LPFILETIME ft) {
  struct tm newtm;
#ifndef HAVE_TIMEGM
  struct tm *gtm;
  time_t time1, time2;
#endif

  newtm.tm_sec  = (fattime & 0x1f) * 2;
  newtm.tm_min  = (fattime >> 5) & 0x3f;
  newtm.tm_hour = (fattime >> 11);
  newtm.tm_mday = (fatdate & 0x1f);
  newtm.tm_mon  = ((fatdate >> 5) & 0x0f) - 1;
  newtm.tm_year = (fatdate >> 9) + 80;
#ifdef HAVE_TIMEGM
  RtlSecondsSince1970ToTime( timegm(&newtm), (LARGE_INTEGER *)ft );
#else

  time1 = mktime(&newtm);
  gtm = gmtime(&time1);
  time2 = mktime(gtm);
  RtlSecondsSince1970ToTime( 2*time1-time2, (LARGE_INTEGER *)ft );
#endif

  return TRUE;
}

/* FIXME
 *  Should it be signed division instead?
 */
static ULONGLONG WINAPI RtlLargeIntegerDivide( ULONGLONG a, ULONGLONG b, ULONGLONG *rem ) {
  ULONGLONG ret = a / b;
  if (rem)
    *rem = a - ret * b;
  return ret;
}


static BOOLEAN WINAPI RtlTimeToSecondsSince1970( const LARGE_INTEGER *Time, LPDWORD Seconds ) {
  ULONGLONG tmp = ((ULONGLONG)Time->u.HighPart << 32) | Time->u.LowPart;
  tmp = RtlLargeIntegerDivide( tmp, 10000000, NULL );
  tmp -= SECS_1601_TO_1970;
  if (tmp > 0xffffffff)
    return FALSE;
  *Seconds = (DWORD)tmp;
  return TRUE;
}

BOOL WINAPI FileTimeToDosDateTime( const FILETIME *ft, LPWORD fatdate,
                                   LPWORD fattime ) {
  LARGE_INTEGER       li;
  ULONG               t;
  time_t              unixtime;
  struct tm*          tm;

  li.u.LowPart = ft->dwLowDateTime;
  li.u.HighPart = ft->dwHighDateTime;
  RtlTimeToSecondsSince1970( &li, &t );
  unixtime = t;
  tm = gmtime( &unixtime );
  if (fattime)
    *fattime = (tm->tm_hour << 11) + (tm->tm_min << 5) + (tm->tm_sec / 2);
  if (fatdate)
    *fatdate = ((tm->tm_year - 80) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday;
  return TRUE;
}

BOOL WINAPI FileTimeToLocalFileTime( const FILETIME *utcft, LPFILETIME localft ) {
  LARGE_INTEGER local, utc;

  utc.u.LowPart = utcft->dwLowDateTime;
  utc.u.HighPart = utcft->dwHighDateTime;
  RtlSystemTimeToLocalTime( &utc, &local );
  localft->dwLowDateTime = local.u.LowPart;
  localft->dwHighDateTime = local.u.HighPart;

  return TRUE;
}


typedef short CSHORT;
typedef struct _TIME_FIELDS {
  CSHORT Year;
  CSHORT Month;
  CSHORT Day;
  CSHORT Hour;
  CSHORT Minute;
  CSHORT Second;
  CSHORT Milliseconds;
  CSHORT Weekday;
}
TIME_FIELDS, *PTIME_FIELDS;

static const int MonthLengths[2][MONSPERYEAR] = {
      {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
      },
      { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
    };

static inline int IsLeapYear(int Year) {
  return Year % 4 == 0 && (Year % 100 != 0 || Year % 400 == 0) ? 1 : 0;
}


static VOID WINAPI RtlTimeToTimeFields(
  const LARGE_INTEGER *liTime,
  PTIME_FIELDS TimeFields) {
  const int *Months;
  int SecondsInDay, DeltaYear;
  int LeapYear, CurMonth;
  long int Days;
  LONGLONG Time = liTime->QuadPart;

  /* Extract millisecond from time and convert time into seconds */
  TimeFields->Milliseconds = (CSHORT) ((Time % TICKSPERSEC) / TICKSPERMSEC);
  Time = Time / TICKSPERSEC;

  /* The native version of RtlTimeToTimeFields does not take leap seconds
   * into account */

  /* Split the time into days and seconds within the day */
  Days = Time / SECSPERDAY;
  SecondsInDay = Time % SECSPERDAY;

  /* compute time of day */
  TimeFields->Hour = (CSHORT) (SecondsInDay / SECSPERHOUR);
  SecondsInDay = SecondsInDay % SECSPERHOUR;
  TimeFields->Minute = (CSHORT) (SecondsInDay / SECSPERMIN);
  TimeFields->Second = (CSHORT) (SecondsInDay % SECSPERMIN);

  /* compute day of week */
  TimeFields->Weekday = (CSHORT) ((EPOCHWEEKDAY + Days) % DAYSPERWEEK);

  /* compute year */
  /* FIXME: handle calendar modifications */
  TimeFields->Year = EPOCHYEAR;
  DeltaYear = Days / DAYSPERQUADRICENTENNIUM;
  TimeFields->Year += DeltaYear * 400;
  Days -= DeltaYear * DAYSPERQUADRICENTENNIUM;
  DeltaYear = Days / DAYSPERNORMALCENTURY;
  TimeFields->Year += DeltaYear * 100;
  Days -= DeltaYear * DAYSPERNORMALCENTURY;
  DeltaYear = Days / DAYSPERNORMALQUADRENNIUM;
  TimeFields->Year += DeltaYear * 4;
  Days -= DeltaYear * DAYSPERNORMALQUADRENNIUM;
  DeltaYear = Days / DAYSPERNORMALYEAR;
  TimeFields->Year += DeltaYear;
  Days -= DeltaYear * DAYSPERNORMALYEAR;

  LeapYear = IsLeapYear(TimeFields->Year);

  /* Compute month of year */
  Months = MonthLengths[LeapYear];
  for (CurMonth = 0; Days >= (long) Months[CurMonth]; CurMonth++)
    Days = Days - (long) Months[CurMonth];
  TimeFields->Month = (CSHORT) (CurMonth + 1);
  TimeFields->Day = (CSHORT) (Days + 1);
}

BOOL WINAPI FileTimeToSystemTime( const FILETIME *ft, LPSYSTEMTIME syst ) {
  TIME_FIELDS tf;
  LARGE_INTEGER t;

  t.u.LowPart = ft->dwLowDateTime;
  t.u.HighPart = ft->dwHighDateTime;
  RtlTimeToTimeFields(&t, &tf);

  syst->wYear = tf.Year;
  syst->wMonth = tf.Month;
  syst->wDay = tf.Day;
  syst->wHour = tf.Hour;
  syst->wMinute = tf.Minute;
  syst->wSecond = tf.Second;
  syst->wMilliseconds = tf.Milliseconds;
  syst->wDayOfWeek = tf.Weekday;
  return TRUE;
}

static void WINAPI RtlLocalTimeToSystemTime( const LARGE_INTEGER *LocalTime,
    PLARGE_INTEGER SystemTime) {
  time_t gmt;
  int bias, daylight;

  gmt = time(NULL);
  bias = TIME_GetBias(gmt, &daylight);

  SystemTime->QuadPart = LocalTime->QuadPart - bias * (LONGLONG)10000000;
}

BOOL WINAPI LocalFileTimeToFileTime( const FILETIME *localft, LPFILETIME utcft ) {
  LARGE_INTEGER local, utc;

  local.u.LowPart = localft->dwLowDateTime;
  local.u.HighPart = localft->dwHighDateTime;
  RtlLocalTimeToSystemTime( &local, &utc );
  utcft->dwLowDateTime = utc.u.LowPart;
  utcft->dwHighDateTime = utc.u.HighPart;

  return TRUE;
}

LONG WINAPI CompareFileTime( const FILETIME *x, const FILETIME *y ) {
  if (!x || !y)
    return -1;

  if (x->dwHighDateTime > y->dwHighDateTime)
    return 1;
  if (x->dwHighDateTime < y->dwHighDateTime)
    return -1;
  if (x->dwLowDateTime > y->dwLowDateTime)
    return 1;
  if (x->dwLowDateTime < y->dwLowDateTime)
    return -1;
  return 0;
}


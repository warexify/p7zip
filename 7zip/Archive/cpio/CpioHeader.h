// Archive/cpio/Header.h

// #pragma once

#ifndef __ARCHIVE_CPIO_HEADER_H
#define __ARCHIVE_CPIO_HEADER_H

#include "Common/Types.h"

namespace NArchive {
namespace NCpio {

#pragma pack( push, PragmacpioHeaders)
#pragma pack( push, 1)

#ifdef __GNUC__   // FIXME - FIXED for gcc 2.95
#define PACKED __attribute__((packed))
#else
#define PACKED
#endif

namespace NFileHeader
{
  namespace NMagic 
  {
    extern const char *kMagic1;
    extern const char *kMagic2;
    extern const char *kEndName;
    extern unsigned short kMagicForRecord2;
    extern unsigned short kMagicForRecord2BE;
  }

  struct CRecord2
  {
    unsigned short c_magic PACKED ;
    short c_dev PACKED ;
    unsigned short c_ino PACKED ;
    unsigned short c_mode PACKED ;
    unsigned short c_uid PACKED ;
    unsigned short c_gid PACKED ;
    unsigned short c_nlink PACKED ;
    short c_rdev PACKED ;
    unsigned short c_mtimes[2] PACKED ;
    unsigned short c_namesize PACKED ;
    unsigned short c_filesizes[2] PACKED ;
  };

  struct CRecord
  {
    char Magic[6] PACKED ;  /* "070701" for "new" portable format, "070702" for CRC format */
    char inode[8] PACKED ;
    char Mode[8] PACKED ;
    char UID[8] PACKED ;
    char GID[8] PACKED ;
    char nlink[8] PACKED ;
    char mtime[8] PACKED ;
    char Size[8] PACKED ; /* must be 0 for FIFOs and directories */
    char DevMajor[8] PACKED ;
    char DevMinor[8] PACKED ;
    char RDevMajor[8] PACKED ;  /*only valid for chr and blk special files*/
    char RDevMinor[8] PACKED ;  /*only valid for chr and blk special files*/
    char NameSize[8] PACKED ; /*count includes terminating NUL in pathname*/
    char ChkSum[8] PACKED ;  /* 0 for "new" portable format; for CRC format the sum of all the bytes in the file  */
    bool CheckMagic()
    { return memcmp(Magic, NMagic::kMagic1, 6) == 0 || 
             memcmp(Magic, NMagic::kMagic2, 6) == 0;  };
  };
}

#pragma pack(pop)
#pragma pack(pop, PragmacpioHeaders)

}}

#endif

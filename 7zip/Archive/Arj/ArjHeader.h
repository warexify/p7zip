// Archive/Arj/Header.h

// #pragma once

#ifndef __ARCHIVE_ARJ_HEADER_H
#define __ARCHIVE_ARJ_HEADER_H

#include "Common/Types.h"

namespace NArchive {
namespace NArj {

const int kMaxBlockSize = 2600;

namespace NSignature
{
  const BYTE kSig0 = 0x60;
  const BYTE kSig1 = 0xEA;
}

#pragma pack( push, Pragma_Arj_Headers)
#pragma pack( push, 1)

#ifdef __GNUC__   // FIXME - FIXED for gcc 2.95
#define PACKED __attribute__((packed))
#else
#define PACKED
#endif

struct CArchiveHeader
{
  // UINT16 BasicHeaderSize;
  BYTE FirstHeaderSize PACKED ;
  BYTE Version PACKED ;
  BYTE ExtractVersion PACKED ;
  BYTE HostOS PACKED ;
  BYTE Flags PACKED ;
  BYTE SecuryVersion PACKED ;
  BYTE FileType PACKED ;
  BYTE Reserved PACKED ;
  UINT32 CreatedTime PACKED ;
  UINT32 ModifiedTime PACKED ;
  UINT32 ArchiveSize PACKED ;
  UINT32 SecurityEnvelopeFilePosition PACKED ;
  UINT16 FilespecPositionInFilename PACKED ;
  UINT16 LengthOfSecurityEnvelopeSata PACKED ;
  BYTE EncryptionVersion PACKED ;
  BYTE LastChapter PACKED ;
};

namespace NFileHeader
{
  namespace NCompressionMethod
  {
    enum EType
    { 
      kStored = 0,
      kCompressed1a = 1,
      kCompressed1b = 2,
      kCompressed1c = 3,
      kCompressed2 = 4,
      kNoDataNoCRC = 8,
      kNoData = 9,
    };
  }
  namespace NFileType
  {
    enum EType
    { 
      kBinary = 0,
      k7BitText = 1,
      kDirectory = 3,
      kVolumeLablel = 4,
      kChapterLabel = 5,
    };
  }
  namespace NFlags
  {
    const BYTE kGarbled = 1;
    const BYTE kVolume = 4;
    const BYTE kExtFile = 8;
    const BYTE kPathSym = 0x10;
    const BYTE kBackup= 0x20;
  }

  struct CHeader
  {
    BYTE FirstHeaderSize PACKED ;
    BYTE Version PACKED ;
    BYTE ExtractVersion PACKED ;
    BYTE HostOS PACKED ;
    BYTE Flags PACKED ;
    BYTE Method PACKED ;
    BYTE FileType PACKED ;
    BYTE Reserved PACKED ;
    UINT32 ModifiedTime PACKED ;
    UINT32 PackSize PACKED ;
    UINT32 Size PACKED ;
    UINT32 FileCRC PACKED ;
    UINT16 FilespecPositionInFilename PACKED ;
    UINT16 FileAccessMode PACKED ;
    BYTE FirstChapter PACKED ;
    BYTE LastChapter PACKED ;
  };
  namespace NHostOS
  {
    enum EEnum
    {
        kMSDOS    = 0,  // filesystem used by MS-DOS, OS/2, Win32 
        // pkarj 2.50 (FAT / VFAT / FAT32 file systems)
        kPRIMOS   = 1,
        kUnix     = 2,  // VAX/VMS
        kAMIGA    = 3,
        kMac      = 4,
        kOS_2     = 5,  // what if it's a minix filesystem? [cjh]
        kAPPLE_GS = 6,  // filesystem used by OS/2 (and NT 3.x)
        kAtari_ST = 7,
        kNext     = 8,
        kVAX_VMS  = 9,
        kWIN95   = 10
    };
  }
}

#pragma pack(pop)
#pragma pack(pop, Pragma_Arj_Headers)

}}

#endif

// Archive/Cab/Header.h

// #pragma once

#ifndef __ARCHIVE_CAB_HEADER_H
#define __ARCHIVE_CAB_HEADER_H

#include "Common/Types.h"

#pragma pack(push, PragmaCabHeaders)
#pragma pack(push, 1)

#ifdef __GNUC__   // FIXME - FIXED for gcc 2.95
#define PACKED __attribute__((packed))
#else
#define PACKED
#endif

namespace NArchive {
namespace NCab {
namespace NHeader{

namespace NArchive {
  
  extern UINT32 kSignature;
  
  namespace NFlags
  {
    const int kPrevCabinet = 0x0001;
    const int kNextCabinet = 0x0002;
    const int kReservePresent = 0x0004;
  }

  struct CBlock
  {
    UINT32  Signature PACKED ;	/* cabinet file signature */
    UINT32  Reserved1 PACKED ;	/* reserved */
    UINT32  Size PACKED ;	/* size of this cabinet file in bytes */
    UINT32  Reserved2 PACKED ;	/* reserved */
    UINT32  FileOffset PACKED ;	/* offset of the first CFFILE entry */
    UINT32  Reserved3 PACKED ;	/* reserved */
    BYTE  VersionMinor PACKED ;	/* cabinet file format version, minor */
    BYTE  VersionMajor PACKED ;	/* cabinet file format version, major */
    UINT16  NumFolders PACKED ;	/* number of CFFOLDER entries in this cabinet */
    UINT16  NumFiles PACKED ;	/* number of CFFILE entries in this cabinet */
    UINT16  Flags PACKED ;	/* cabinet file option indicators */
    UINT16  SetID PACKED ;	/* must be the same for all cabinets in a set */
    UINT16  CabinetNumber PACKED ;	/* number of this cabinet file in a set */
  };

  struct CPerDataSizes
  {
    UINT16  PerCabinetAreaSize PACKED ; 	/* (optional) size of per-cabinet reserved area */
    BYTE  PerFolderAreaSize PACKED ; 	/* (optional) size of per-folder reserved area */
    BYTE  PerDatablockAreaSize PACKED ; 	/* (optional) size of per-datablock reserved area */
  };

    /*
    BYTE  abReserve[];	// (optional) per-cabinet reserved area
    BYTE  szCabinetPrev[];	// (optional) name of previous cabinet file
    BYTE  szDiskPrev[];	// (optional) name of previous disk
    BYTE  szCabinetNext[];	// (optional) name of next cabinet file
    BYTE  szDiskNext[];	// (optional) name of next disk
    */
}

namespace NCompressionMethodMajor
{
  const BYTE kNone = 0;
  const BYTE kMSZip = 1;
  const BYTE kQuantum = 2;
  const BYTE kLZX = 3;
}

struct CFolder
{
  UINT32  DataStart PACKED ;	// offset of the first CFDATA block in this folder
  UINT16  NumDataBlocks PACKED ;	// number of CFDATA blocks in this folder
  BYTE CompressionTypeMajor PACKED ;
  BYTE CompressionTypeMinor PACKED ;
  // BYTE  abReserve[];	// (optional) per-folder reserved area
  BYTE GetCompressionMethod() const { return CompressionTypeMajor & 0xF; }
};

const int kFileNameIsUTFAttributeMask = 0x80;

namespace NFolderIndex
{
  const int kContinuedFromPrev    = 0xFFFD;
  const int kContinuedToNext      = 0xFFFE;
  const int kContinuedPrevAndNext = 0xFFFF;
  inline UINT16 GetRealFolderIndex(UINT16 aNumFolders, UINT16 aFolderIndex)
  {
    switch(aFolderIndex)
    {
      case kContinuedFromPrev:
        return 0;
      case kContinuedToNext:
      case kContinuedPrevAndNext:
        return aNumFolders - 1;
      default:
        return aFolderIndex;
    }
  }
}

struct CFile
{
  UINT32  UnPackSize PACKED ;	/* uncompressed size of this file in bytes */
  UINT32  UnPackOffset PACKED ;	/* uncompressed offset of this file in the folder */
  UINT16  FolderIndex PACKED ;	/* index into the CFFOLDER area */
  UINT16  PureDate PACKED ;
  UINT16  PureTime PACKED ; /* Time */
  UINT16  Attributes PACKED ;	/* attribute flags for this file */
  //BYTE  szName[];	/* name of this file */
};

}}}

#pragma pack(pop)
#pragma pack(pop, PragmaCabHeaders)

#endif

// Archive/Zip/Header.h

// #pragma once

#ifndef __ARCHIVE_ZIP_HEADER_H
#define __ARCHIVE_ZIP_HEADER_H

#include "Common/Types.h"

namespace NArchive {
namespace NZip {

#pragma pack( push, PragmaZipHeaders)
#pragma pack( push, 1)


#ifdef __GNUC__   // FIXME - FIXED for gcc 2.95
#define PACKED __attribute__((packed))
#else
#define PACKED
#endif

namespace NSignature
{
  extern UINT32 kLocalFileHeader;
  extern UINT32 kDataDescriptor;
  extern UINT32 kCentralFileHeader;
  extern UINT32 kEndOfCentralDir;
  
  static const UINT32 kMarkerSize = 4;
}

struct CEndOfCentralDirectoryRecord
{
  UINT16 ThisDiskNumber PACKED ;
  UINT16 StartCentralDirectoryDiskNumber PACKED ;
  UINT16 NumEntriesInCentaralDirectoryOnThisDisk PACKED ;
  UINT16 NumEntriesInCentaralDirectory PACKED ;
  UINT32 CentralDirectorySize PACKED ;
  UINT32 CentralDirectoryStartOffset PACKED ;
  UINT16 CommentSize PACKED ;
};

struct CEndOfCentralDirectoryRecordFull
{
  UINT32 Signature PACKED ;
  CEndOfCentralDirectoryRecord Header PACKED ;
};

namespace NFileHeader
{
  struct CVersion
  {
    BYTE Version PACKED ;
    BYTE HostOS PACKED ;
  };
  
  namespace NCompressionMethod
  {
    enum EType
    { 
      kStored = 0,
      kShrunk = 1,
      kReduced1 = 2,
      kReduced2 = 3,
      kReduced3 = 4,
      kReduced4 = 5,
      kImploded = 6,
      kReservedTokenizing = 7, // reserved for tokenizing
      kDeflated = 8, 
      kDeflated64 = 9,
      kPKImploding = 10,
      
      kBZip2 = 12
    };
    const int kNumCompressionMethods = 11;
    const BYTE kMadeByProgramVersion = 20;
    
    const BYTE kDeflateExtractVersion = 20;
    const BYTE kStoreExtractVersion = 10;
    
    const BYTE kSupportedVersion   = 20;
  }

  struct CLocalBlock
  {
    CVersion ExtractVersion PACKED ;
    UINT16 Flags PACKED ;
    UINT16 CompressionMethod PACKED ;
    UINT32 Time PACKED ;
    UINT32 FileCRC PACKED ;
    UINT32 PackSize PACKED ;
    UINT32 UnPackSize PACKED ;
    UINT16 NameSize PACKED ;
    UINT16 ExtraSize PACKED ;
  };

  struct CDataDescriptor
  {
    UINT32 Signature PACKED ;
    UINT32 FileCRC PACKED ;
    UINT32 PackSize PACKED ;
    UINT32 UnPackSize PACKED ;
  };

  struct CLocalBlockFull
  {
    UINT32 Signature PACKED ;
    CLocalBlock Header PACKED ;
  };
  
  struct CBlock
  {
    CVersion MadeByVersion PACKED ;
    CVersion ExtractVersion PACKED ;
    UINT16 Flags PACKED ;
    UINT16 CompressionMethod PACKED ;
    UINT32 Time PACKED ;
    UINT32 FileCRC PACKED ;
    UINT32 PackSize PACKED ;
    UINT32 UnPackSize PACKED ;
    UINT16 NameSize PACKED ;
    UINT16 ExtraSize PACKED ;
    UINT16 CommentSize PACKED ;
    UINT16 DiskNumberStart PACKED ;
    UINT16 InternalAttributes PACKED ;
    UINT32 ExternalAttributes PACKED ;
    UINT32 LocalHeaderOffset PACKED ;
  };
  
  struct CBlockFull
  {
    UINT32 Signature PACKED ;
    CBlock Header PACKED ;
  };
  
  namespace NFlags 
  {
    const int kNumUsedBits = 4;
    const int kUsedBitsMask = (1 << kNumUsedBits) - 1;
    
    const int kEncryptedMask   = 1 << 0;
    const int kDescriptorUsedMask   = 1 << 3;
    
    const int kImplodeDictionarySizeMask = 1 << 1;
    const int kImplodeLiteralsOnMask     = 1 << 2;
    
    const int kDeflateTypeBitStart = 1;
    const int kNumDeflateTypeBits = 2;
    const int kNumDeflateTypes = (1 << kNumDeflateTypeBits);
    const int kDeflateTypeMask = (1 << kNumDeflateTypeBits) - 1;
  }
  
  namespace NHostOS
  {
    enum EEnum
    {
      kFAT      = 0,  // filesystem used by MS-DOS, OS/2, Win32 
        // pkzip 2.50 (FAT / VFAT / FAT32 file systems)
        kAMIGA    = 1,
        kVMS      = 2,  // VAX/VMS
        kUnix     = 3,
        kVM_CMS   = 4,
        kAtari    = 5,  // what if it's a minix filesystem? [cjh]
        kHPFS     = 6,  // filesystem used by OS/2 (and NT 3.x)
        kMac      = 7,
        kZ_System = 8,
        kCPM      = 9,
        kTOPS20   = 10, // pkzip 2.50 NTFS 
        kNTFS     = 11, // filesystem used by Windows NT 
        kQDOS     = 12, // SMS/QDOS
        kAcorn    = 13, // Archimedes Acorn RISC OS
        kVFAT     = 14, // filesystem used by Windows 95, NT
        kMVS      = 15,
        kBeOS     = 16, // hybrid POSIX/database filesystem
        // BeBOX or PowerMac 
        kTandem   = 17,
        kTHEOS    = 18
    };
    // const int kNumHostSystems = 19;
  }
  namespace NUnixAttribute
  {
    const UINT32 kIFMT   =   0170000;     /* Unix file type mask */
    
    const UINT32 kIFDIR  =   0040000;     /* Unix directory */
    const UINT32 kIFREG  =   0100000;     /* Unix regular file */
    const UINT32 kIFSOCK =   0140000;     /* Unix socket (BSD, not SysV or Amiga) */
    const UINT32 kIFLNK  =   0120000;     /* Unix symbolic link (not SysV, Amiga) */
    const UINT32 kIFBLK  =   0060000;     /* Unix block special       (not Amiga) */
    const UINT32 kIFCHR  =   0020000;     /* Unix character special   (not Amiga) */
    const UINT32 kIFIFO  =   0010000;     /* Unix fifo    (BCC, not MSC or Amiga) */
    
    const UINT32 kISUID  =   04000;       /* Unix set user id on execution */
    const UINT32 kISGID  =   02000;       /* Unix set group id on execution */
    const UINT32 kISVTX  =   01000;       /* Unix directory permissions control */
    const UINT32 kENFMT  =   kISGID;   /* Unix record locking enforcement flag */
    const UINT32 kIRWXU  =   00700;       /* Unix read, write, execute: owner */
    const UINT32 kIRUSR  =   00400;       /* Unix read permission: owner */
    const UINT32 kIWUSR  =   00200;       /* Unix write permission: owner */
    const UINT32 kIXUSR  =   00100;       /* Unix execute permission: owner */
    const UINT32 kIRWXG  =   00070;       /* Unix read, write, execute: group */
    const UINT32 kIRGRP  =   00040;       /* Unix read permission: group */
    const UINT32 kIWGRP  =   00020;       /* Unix write permission: group */
    const UINT32 kIXGRP  =   00010;       /* Unix execute permission: group */
    const UINT32 kIRWXO  =   00007;       /* Unix read, write, execute: other */
    const UINT32 kIROTH  =   00004;       /* Unix read permission: other */
    const UINT32 kIWOTH  =   00002;       /* Unix write permission: other */
    const UINT32 kIXOTH  =   00001;       /* Unix execute permission: other */
  }
  
  namespace NAmigaAttribute
  {
    const UINT32 kIFMT     = 06000;       /* Amiga file type mask */
    const UINT32 kIFDIR    = 04000;       /* Amiga directory */
    const UINT32 kIFREG    = 02000;       /* Amiga regular file */
    const UINT32 kIHIDDEN  = 00200;       /* to be supported in AmigaDOS 3.x */
    const UINT32 kISCRIPT  = 00100;       /* executable script (text command file) */
    const UINT32 kIPURE    = 00040;       /* allow loading into resident memory */
    const UINT32 kIARCHIVE = 00020;       /* not modified since bit was last set */
    const UINT32 kIREAD    = 00010;       /* can be opened for reading */
    const UINT32 kIWRITE   = 00004;       /* can be opened for writing */
    const UINT32 kIEXECUTE = 00002;       /* executable image, a loadable runfile */
    const UINT32 kIDELETE  = 00001;      /* can be deleted */
  }
}

#pragma pack(pop)
#pragma pack(pop, PragmaZipHeaders)

}}

#endif

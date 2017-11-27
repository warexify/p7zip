// Windows/FileIO.h

#ifndef __WINDOWS_FILEIO_H
#define __WINDOWS_FILEIO_H

namespace NWindows {
namespace NFile {
namespace NIO {

class CFileBase
{
protected:
  bool _fileIsOpen;
  t_file_handle  _handle;
  bool Create(LPCTSTR fileName, DWORD desiredAccess,
      DWORD shareMode, DWORD creationDisposition,  DWORD flagsAndAttributes);
 #ifndef _UNICODE
  bool Create(LPCWSTR fileName, DWORD desiredAccess,
      DWORD shareMode, DWORD creationDisposition,  DWORD flagsAndAttributes);
  #endif

public:
  CFileBase(): _fileIsOpen(false) {};
  virtual ~CFileBase();

  virtual bool Close();

  bool GetLength(UInt64 &length) const;

  bool Seek(Int64 distanceToMove, DWORD moveMethod, UInt64 &newPosition) const;
  bool Seek(UInt64 position, UInt64 &newPosition);
};

class CInFile: public CFileBase
{
public:
  bool Open(LPCTSTR fileName, DWORD shareMode, 
      DWORD creationDisposition,  DWORD flagsAndAttributes);
  bool Open(LPCTSTR fileName);

  #ifndef _UNICODE
  bool Open(LPCWSTR fileName, DWORD shareMode, 
      DWORD creationDisposition,  DWORD flagsAndAttributes);
  bool Open(LPCWSTR fileName);
  #endif
  bool Read(void *data, UInt32 size, UInt32 &processedSize);
};

class COutFile: public CFileBase
{
  DWORD m_CreationDisposition;
public:
  COutFile(): m_CreationDisposition(CREATE_NEW){};
  bool Open(LPCTSTR fileName, DWORD shareMode, 
      DWORD creationDisposition, DWORD flagsAndAttributes);
  bool Open(LPCTSTR fileName);
  bool Create(LPCTSTR fileName, bool createAlways);
 
  #ifndef _UNICODE
  bool Open(LPCWSTR fileName, DWORD shareMode, 
      DWORD creationDisposition, DWORD flagsAndAttributes);
  bool Open(LPCWSTR fileName);
  bool Open(LPCWSTR fileName, DWORD creationDisposition);
  bool Create(LPCWSTR fileName, bool createAlways);
  #endif

/*
  void SetOpenCreationDisposition(DWORD creationDisposition)
    { m_CreationDisposition = creationDisposition; }
*/
    void SetOpenCreationDispositionCreateAlways()
    { m_CreationDisposition = CREATE_ALWAYS; }

  bool SetTime(const FILETIME *creationTime,
      const FILETIME *lastAccessTime, const FILETIME *lastWriteTime);
  bool SetLastWriteTime(const FILETIME *lastWriteTime);
  bool Write(const void *data, UInt32 size, UInt32 &processedSize);
  bool SetEndOfFile();
  bool SetLength(UInt64 length);
};

}}}

#endif

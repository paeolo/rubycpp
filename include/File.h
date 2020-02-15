#ifndef DATA_H
#define DATA_H

#include "gbfs.h"
#include <gba_types.h>

enum FileType
{
  BPP4,
  BPP8,
  GBAPAL,
  GBABG,
  JSON
};

class File
{
  public:
    File(const char* fileName, const int fileType);
    void copyTo(volatile void *destination);
    const bool exists();
    const void* data();
    const u32 size();

  private:
    const void* _data;
    u32 _size;
};

#endif
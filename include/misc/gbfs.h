/* -----------------------------------------------------------------
File: gbfs.h
Description: Access object in a GBFS file

Copyright 2002 Damian Yerrick

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
----------------------------------------------------------------- */

#ifndef INCLUDE_GBFS_H
#define INCLUDE_GBFS_H
#ifdef __cplusplus
extern "C" {
#endif

#include <gba_types.h>
#include <stdio.h>

/* to make a 300 KB space called samples do GBFS_SPACE(samples, 300) */

#define GBFS_SPACE(filename, kbytes) \
const char filename[(kbytes)*1024] __attribute__ ((aligned (16))) = \
  "PinEightGBFSSpace-" #filename "-" #kbytes ;

typedef struct GBFS_FILE
{
  char magic[16];    /* "PinEightGBFS\r\n\032\n" */
  u32  total_len;    /* total length of archive */
  u16  dir_off;      /* offset in bytes to directory */
  u16  dir_nmemb;    /* number of files */
  char reserved[8];  /* for future use */
} GBFS_FILE;

typedef struct GBFS_ENTRY
{
  char name[24];     /* filename, nul-padded */
  u32  len;          /* length of object in bytes */
  u32  data_offset;  /* in bytes from beginning of file */
} GBFS_ENTRY;

const void *gbfs_get_obj(const GBFS_FILE *file, const char *name, u32 *len);
size_t gbfs_count_objs(const GBFS_FILE *file);

#ifdef __cplusplus
}
#endif
#endif
/* -----------------------------------------------------------------
File: libgbfs.c
Description: Access object in a GBFS file

Copyright 2002-2004 Damian Yerrick

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

typedef unsigned short u16;
typedef unsigned long u32;

#include <stdlib.h>
#include <string.h>
#include "gbfs.h"

static int namecmp(const void *a, const void *b)
{
  return memcmp(a, b, 24);
}

const void *gbfs_get_obj(const GBFS_FILE *file, const char *name, u32 *len)
{
  char key[24] = {0};
  const GBFS_ENTRY *dirbase = (const GBFS_ENTRY *)((const char *)file + file->dir_off);
  size_t n_entries = file->dir_nmemb;
  const GBFS_ENTRY *here;

  strncpy(key, name, 24);

  here = bsearch(key, dirbase, n_entries, sizeof(GBFS_ENTRY), namecmp);
  if(!here)
  {
    return NULL;
  }
  if(len)
  {
    *len = here->len;
  }

  return (char *)file + here->data_offset;
}

size_t gbfs_count_objs(const GBFS_FILE *file)
{
  return file ? file->dir_nmemb : 0;
}
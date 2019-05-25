#ifndef PALETTE_H
#define PALETTE_H

#include <gba_types.h>
#include <gba_base.h>

/* COLOR */

#define RGB(red, green, blue) (Color {red, green, blue, 0})

#define BLACK RGB(0, 0, 0)
#define BLANK RGB(31, 31, 31)

typedef struct Color
{
  unsigned int red:5;
  unsigned int green:5;
  unsigned int blue:5;
  unsigned int alpha:1;
  static Color Integer(int i);
  static Color centroid(Color const& x, Color const& y, int fader);
  constexpr operator int() const {return  (blue << 10) + (green << 5) + red;}
} __attribute__((packed, aligned(1))) Color;

/* PALETTE */

typedef struct PALETTE_t
{
    Color BG[256];  // BG Palette (512 bytes, 256 colors)
    Color OBJ[256];  // OBJ Palette (512 bytes, 256 colors)
} PALETTE_t;

#define PALETTE (*(volatile PALETTE_t *) 0x5000000)
#define PALETTE_SIZE 0x400
#define PALETTE_LENGTH 0x200

class Palette
{
  public:
    static void Copy(int source, int destination, int offset);
    static void Load(const char* paletteName, int position);
    static void FillData(const Color color);
    static void FillBuffer(const Color color);
    static void Flush();
    EWRAM_DATA static Color data[PALETTE_LENGTH];
    EWRAM_DATA static Color buffer[PALETTE_LENGTH];
};

#endif
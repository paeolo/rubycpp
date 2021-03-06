#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <gba_types.h>
#include <gba_base.h>
#include <gba_affine.h>

/* TILE */

typedef struct Tile4
{
  u8 data[32];
} __attribute__((packed, aligned(1))) Tile4;

typedef struct Entry
{
  unsigned int tileNumber:10;
  unsigned int horizontalFlip:1;
  unsigned int verticalFlip:1;
  unsigned int paletteNumber:4;
  constexpr operator int() const
  {
    return  (paletteNumber << 12) + (verticalFlip << 11) + (horizontalFlip << 10) + tileNumber;
  }
} __attribute__((packed, aligned(1))) Entry;

typedef Tile4 CharBlock[512];
typedef Entry ScreenBlock[32][32];

enum ColorNumber
{
  COLOR_0, COLOR_1, COLOR_2, COLOR_3,
  COLOR_4, COLOR_5, COLOR_6, COLOR_7,
  COLOR_8, COLOR_9, COLOR_10, COLOR_11,
  COLOR_12, COLOR_13, COLOR_14, COLOR_15,
};

/* BACKGROUND */

typedef union BACKGROUND_t
{
  CharBlock charBlock[4];
  ScreenBlock screenBlock[32];
} BACKGROUND_t;

#define BACKGROUND (*(volatile BACKGROUND_t *) 0x6000000)
#define BACKGROUND_SIZE 0x10000

enum AffineBG
{
  BG_AFFINE_0 = 0,
  BG_AFFINE_1 = 1
};

class Background
{
  public:
    static void LoadTile4(const char* tileName, int charBlock, int tileNumber);
    static void CreateTile4(ColorNumber colorNumber, int charBlock, int tileNumber);
    static void LoadTile8(const char* tileName, int charBlock, int tileNumber);
    static void LoadTileMap(const char* tileMapName, int screenBlock, int entryNumber);
    static void CreateTileMap16(unsigned int tileNum, unsigned int paletteNum, int screenBlock, int lineNum, int size);
    static void AffineSet(BGAffineSource &source, AffineBG background);
};

#endif

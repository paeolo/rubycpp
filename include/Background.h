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
} __attribute__((packed, aligned(1))) Entry;

typedef Tile4 CharBlock[512];
typedef Entry ScreenBlock[32][32];

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
    static void LoadTile8(const char* tileName, int charBlock, int tileNumber);
    static void LoadTileMap(const char* tileMapName, int screenBlock, int entryNumber);
    static void AffineSet(BGAffineSource &source, AffineBG background);
};

#endif

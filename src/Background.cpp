#include "Background.h"
#include "dma.h"
#include "File.h"
#include "register.h"


void Background::LoadTile4(const char* tileName, int charBlock, int tileNumber)
{
    File file(tileName, FileType::BPP4);
    if(file.exists())
        file.copyTo(&BACKGROUND.charBlock[charBlock][tileNumber]);
}

void Background::CreateTile4(ColorNumber colorNumber, int charBlock, int tileNumber)
{
    u16 byte = (colorNumber << 12) + (colorNumber << 8) + (colorNumber << 4) + colorNumber;
    dma::Fill16(3, byte, &BACKGROUND.charBlock[charBlock][tileNumber], 32);
}

void Background::LoadTile8(const char* tileName, int charBlock, int tileNumber)
{
    File file(tileName, FileType::BPP8);
    if(file.exists())
        file.copyTo(&BACKGROUND.charBlock[charBlock][tileNumber]);
}

void Background::LoadTileMap(const char* tileMapName, int screenBlock, int entryNumber)
{
    File file(tileMapName, FileType::GBABG);
    if(file.exists())
        file.copyTo(&BACKGROUND.screenBlock[screenBlock][entryNumber]);
}

void Background::CreateTileMap16(unsigned int tileNum, unsigned int paletteNum, int screenBlock, int lineNum, int size)
{
    Entry entry = {
        .tileNumber = tileNum,
        .horizontalFlip = 0,
        .verticalFlip = 0,
        .paletteNumber = paletteNum
    };
    dma::Fill16(3, entry, &BACKGROUND.screenBlock[screenBlock][lineNum], size << 1);
}

void Background::AffineSet(BGAffineSource &source, AffineBG background)
{
    BGAffineDest dest;
    BgAffineSet(&source, &dest, 1);
    BGAFF[background].A = dest.pa;
    BGAFF[background].B = dest.pb;
    BGAFF[background].C = dest.pc;
    BGAFF[background].D = dest.pd;
    BGAFF[background].X = dest.x;
    BGAFF[background].Y = dest.y;
}

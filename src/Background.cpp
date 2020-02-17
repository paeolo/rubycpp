#include "Background.h"
#include "File.h"
#include "register.h"


void Background::LoadTile4(const char* tileName, int charBlock, int tileNumber)
{
    File file(tileName, FileType::BPP4);
    if(file.exists())
        file.copyTo(&BACKGROUND.charBlock[charBlock][tileNumber]);
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

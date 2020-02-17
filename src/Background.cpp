#include "Background.h"
#include "File.h"
#include "register.h"
#include "trig.h"

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

void Background::rotate(Fixed x, Fixed y, Fixed rho, int theta, AffineBG bg)
{
    BGAFF[bg].A = Cos(theta).raw;
    BGAFF[bg].B = Sin(theta).raw;
    BGAFF[bg].C = - Sin(theta).raw;
    BGAFF[bg].D = Cos(theta).raw;
}

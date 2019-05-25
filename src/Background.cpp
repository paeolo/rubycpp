#include "Background.h"
#include "File.h"


void Background::LoadTile4(const char* tileName, int charBlock, int tileNumber)
{
    File file(tileName, FileType::BPP4);
    if(file.exists())
        file.copyTo(&BACKGROUND.charBlock[charBlock][tileNumber]);
}

void Background::LoadTileMap(const char* tileMapName, int screenBlock, int entryNumber)
{
    File file(tileMapName, FileType::GBABG);
    if(file.exists())
        file.copyTo(&BACKGROUND.screenBlock[screenBlock][entryNumber]);
}
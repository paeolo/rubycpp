#include "Allocator.h"

#include <gba_types.h>
#include <gba_base.h>

#include "Background.h"
#include "Palette.h"
#include "Sprite.h"
#include "SpriteGroup.h"

#include "MemoryPool.h"
#include "Pool.h"

#define SPRITE_MAP_SIZE 64
#define SPRITE_GROUP_MAP_SIZE 16
#define PALETTE_MAP_SIZE 16
#define TILE_MAP_SIZE 16

/*
* Memory Management 
*/
EWRAM_DATA MemoryPool<Sprite, 64> spritePool;
EWRAM_DATA static Pool<32> matrixPool;
int paletteNum = 0;
int tileNum = 0;

/*
* Map Management 
*/
EWRAM_DATA Sprite* spriteMap[SPRITE_MAP_SIZE] = { nullptr };
EWRAM_DATA SpriteGroup* spriteGroupMap[SPRITE_GROUP_MAP_SIZE] = { nullptr };
EWRAM_DATA int paletteMap[PALETTE_MAP_SIZE] = { -1 };
EWRAM_DATA int tileMap[TILE_MAP_SIZE] = { -1 };

/*
* Sprite
*/
Sprite* Allocator::Sprite::getByTag(int tag)
{
    return spriteMap[tag & (SPRITE_MAP_SIZE - 1)];
}
void Allocator::Sprite::setByTag(int tag, ::Sprite* sprite)
{
    spriteMap[tag & (SPRITE_MAP_SIZE - 1)] = sprite;
}
void Allocator::Sprite::eraseTag(int tag)
{
    spriteMap[tag & (SPRITE_MAP_SIZE - 1)] = nullptr;
}

Sprite* Allocator::Sprite::allocate()
{
    return spritePool.allocate();
}
void Allocator::Sprite::deallocate(::Sprite* sprite)
{
    spritePool.deallocate(sprite);
}

/*
* Sprite Group
*/
SpriteGroup* Allocator::SpriteGroup::getByTag(int tag)
{
    return spriteGroupMap[tag & (SPRITE_GROUP_MAP_SIZE - 1)]; 
}
void Allocator::SpriteGroup::setByTag(int tag, ::SpriteGroup* group)
{
    spriteGroupMap[tag & (SPRITE_GROUP_MAP_SIZE - 1)] = group;
}
void Allocator::SpriteGroup::eraseTag(int tag)
{ 
    spriteGroupMap[tag & (SPRITE_GROUP_MAP_SIZE - 1)] = nullptr;
}

/*
* Matrix 
*/

int Allocator::Matrix::allocate()
{ 
    return matrixPool.allocate();
}
void Allocator::Matrix::deallocate(int matrixNum)
{
    matrixPool.deallocate(matrixNum);
}

/*
* Palette
*/
int Allocator::Palette::getByTag(int tag)
{
    return paletteMap[tag & (PALETTE_MAP_SIZE -1)];
}
void Allocator::Palette::setByTag(int tag, int paletteNum)
{
    paletteMap[tag & (PALETTE_MAP_SIZE -1)] = paletteNum;
}
void Allocator::Palette::eraseTag(int tag)
{ 
    paletteMap[tag & (PALETTE_MAP_SIZE -1)] = -1;
}
int Allocator::Palette::allocate()
{
    return paletteNum++;
}
void Allocator::Palette::deallocate(int paletteNum) { }

/*
* Tile 
*/
int Allocator::Tile::getByTag(int tag)
{
    return tileMap[tag & (TILE_MAP_SIZE -1)];
}
void Allocator::Tile::setByTag(int tag, int tileNum)
{
    tileMap[tag & (TILE_MAP_SIZE -1)] = tileNum;
}
void Allocator::Tile::eraseTag(int tag)
{ 
    tileMap[tag & (TILE_MAP_SIZE -1)] = -1;
}
int Allocator::Tile::allocate(const char* tileName)
{
    int result = tileNum;
    tileNum += ::Sprite::LoadTile4(tileName, tileNum);
    return result;
}
void Allocator::Tile::deallocate(int tileNum) { }

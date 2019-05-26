#include "Allocator.h"
#include "dma.h"
#include "File.h"
#include "Fixed.h"
#include "Sprite.h"
#include "trig.h"

EWRAM_DATA OAM_t Sprite::buffer;

int Sprite::LoadTile4(const char* tileName, int tileNumber)
{
    File file(tileName, FileType::BPP4);
    if(file.exists())
    {
        file.copyTo(&OBJ_VRAM[tileNumber]);
        return file.size() >> 5;
    }
    return 0;
}

void Sprite::Flush()
{
    dma::Copy16(3, &Sprite::buffer, &OAM_RAM, OAM_SIZE);
}

Sprite::Sprite(int tag, int paletteNum, int tileNum): Sprite()
{
    this->_tag = tag;
    entry.paletteNum = paletteNum;
    this->_tile = tileNum;
}

Sprite::~Sprite()
{
    this->visible = false;
    this->scale(1, 1);
    this->update();
}

void Sprite::update()
{
    AffineObject::update();
    if(this->visible)
    {
        entry.tileNum = _tile + tileOffset;
        entry.priority = priority;
        entry.x = this->pos1.x + this->pos2.x + _center.x;
        entry.y = this->pos1.y + this->pos2.y + _center.y;
        entry.coefficient = buffer.Object[_id].coefficient;
        buffer.Object[_id] = entry;
    }
    else
    {
        ObjectEntry entry = ObjectEntry();
        entry.x = 304;
        entry.y = 160;
        entry.affineMode = AFFINE_HIDDEN;
        entry.priority = 3;
        entry.coefficient = buffer.Object[_id].coefficient;
        buffer.Object[_id] = entry;
    }
}

void Sprite::destroy()
{
    allocator.destroySprite(_tag);
}

void Sprite::scale(Fixed a, Fixed b)
{
    buffer.Matrix[entry.matrixNum].A = a;
    buffer.Matrix[entry.matrixNum].B = 0;
    buffer.Matrix[entry.matrixNum].C = 0;
    buffer.Matrix[entry.matrixNum].D = b;
}

void Sprite::rotate(Fixed a, Fixed b, int theta)
{
    buffer.Matrix[entry.matrixNum].A = a * Cos(theta);
    buffer.Matrix[entry.matrixNum].B = a * Sin(theta);
    buffer.Matrix[entry.matrixNum].C = -b * Sin(theta);
    buffer.Matrix[entry.matrixNum].D = b * Cos(theta);
}

void Sprite::setShape(int shape, int size, int mode)
{

    static const s8 centerTable[3][4][2] =
    {
        {{-4, -4}, {-8, -8}, {-16, -16}, {-32, -32},},
        {{-8, -4}, {-16, -4}, {-16, -8}, {-32, -16},},
        {{-4, -8}, {-4, -16}, {-8, -16}, {-16, -32},},
    };
    
    entry.shape = shape;
    entry.size = size;
    entry.affineMode = mode;
    if(mode == AFFINE_DOUBLE)
    {
        _center.x = 2*centerTable[shape][size][0];
        _center.y = 2*centerTable[shape][size][1];
    }
    else
    {
        _center.x = centerTable[shape][size][0];
        _center.y = centerTable[shape][size][1];
    }
    if(mode & AFFINE_ENABLE)
        entry.matrixNum = _id;
}

void Sprite::setId(int id)
{
    this->_id = id;
}
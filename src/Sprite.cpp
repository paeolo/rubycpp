#include "dma.h"
#include "trig.h"

#include "Allocator.h"
#include "Engine.h"
#include "File.h"
#include "Fixed.h"
#include "Palette.h"
#include "Sprite.h"

EWRAM_DATA OAM_t Sprite::buffer;
IWRAM_DATA SpriteSorter Sprite::sorter;

IWRAM_DATA const ObjectEntry Sprite::emptyEntry = ObjectEntry::makeEmptyEntry();

ObjectEntry ObjectEntry::makeEmptyEntry()
{
    ObjectEntry entry = ObjectEntry();
    entry.x = 304;
    entry.y = 160;
    entry.affineMode = AFFINE_HIDDEN;
    entry.priority = 3;
    return entry;
}

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

void* Sprite::operator new(size_t size)
{
    return Allocator::Sprite::allocate();
}

void Sprite::operator delete(void* ptr)
{
    Allocator::Sprite::deallocate((Sprite*) ptr);
}

Sprite::Sprite(int paletteNum, int tileNum, int tag, bool insert_updater): Sprite()
{
    entry.paletteNum = paletteNum;
    _tile = tileNum;
    _tag = tag;
    if(tag != -1)
        Allocator::Sprite::setByTag(tag, this);
    if(insert_updater)
        Engine::updater.insert(this);
    Sprite::sorter.insert(this);
}

Sprite::~Sprite()
{
    if (_tag != -1)
        Allocator::Sprite::eraseTag(_tag);
    if (_matrix >= 0)
        Allocator::Matrix::deallocate(_matrix);
}

void Sprite::update()
{
    update({0, 0});
}

void Sprite::update(pos_t offset)
{
    if (this->visible)
    {
        entry.tileNum = _tile + tileOffset;
        entry.priority = priority;
        entry.x = this->pos1.x + this->pos2.x + offset.x + _center.x;
        entry.y = this->pos1.y + this->pos2.y + offset.y + _center.y;
        entry.coefficient = buffer.Object[_id].coefficient;
        Sprite::buffer.Object[_id] = entry;
    }
    else
    {
        ObjectEntry entry = Sprite::emptyEntry;
        entry.coefficient = buffer.Object[_id].coefficient;
        buffer.Object[_id] = entry;
    }
}

void Sprite::scale(Fixed a, Fixed b)
{
    buffer.Matrix[entry.matrix].A = a;
    buffer.Matrix[entry.matrix].B = 0;
    buffer.Matrix[entry.matrix].C = 0;
    buffer.Matrix[entry.matrix].D = b;
}

void Sprite::rotate(Fixed a, Fixed b, int theta)
{
    buffer.Matrix[entry.matrix].A = a * Cos(theta);
    buffer.Matrix[entry.matrix].B = a * Sin(theta);
    buffer.Matrix[entry.matrix].C = -b * Sin(theta);
    buffer.Matrix[entry.matrix].D = b * Cos(theta);
}

void Sprite::setShape(SpriteShape shape, SpriteSize size, AffineMode mode)
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
    if((mode & AFFINE_ENABLE) && _matrix < 0)
    {
        _matrix = Allocator::Matrix::allocate();
        entry.matrix= _matrix;
    }
}

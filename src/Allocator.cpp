#include "Allocator.h"
#include "Palette.h"
#include "Sprite.h"

Sprite* Allocator::createSprite(int tag, int paletteTag, int tileTag)
{
    if (tag > 0)
    {
        Sprite* sprite = new Sprite
        (
            tag,
            this->getPalette(paletteTag),
            this->getTile(tileTag)
        );
        sprite->setId(_spriteId);
        _sprite[tag] = sprite;
        ++_spriteId;
        return sprite;
    }
    else
        return nullptr;
}

void Allocator::createPalette(const char* paletteName, int tag)
{
    if(tag > 0)
    {
        Palette::Load(paletteName, 16 + _paletteId);
        _palette[tag] = _paletteId;
        ++_paletteId;
    }
}

void Allocator::createTile(const char* tileName, int tag)
{
    if (tag > 0)
    {
        int size = Sprite::LoadTile4(tileName, _tileId);
        _tile[tag] = _tileId;
        _tileId += size;
    }
}

void Allocator::destroySprite(int tag)
{
    delete _sprite[tag];
    _sprite.erase(tag);
    --_spriteId;
}

void Allocator::destroyPalette(int tag)
{
    _palette.erase(tag);
    --_paletteId;
}

Sprite* Allocator::getSprite(int tag)
{
    if(tag > 0)
        return _sprite[tag];
    else
        return nullptr;
}

int Allocator::getPalette(int tag)
{
    return _palette[tag];
}

int Allocator::getTile(int tag)
{
    return _tile[tag];
}

void Allocator::destroyAllPalette()
{
    _palette.clear();
    _paletteId = 0;
}

void Allocator::destroyAllSprite()
{
    std::map<int, Sprite*>::iterator it;
    for(it = _sprite.begin(); it != _sprite.end(); ++it)
        delete it->second;
    _sprite.clear();
    _spriteId = 0;
}
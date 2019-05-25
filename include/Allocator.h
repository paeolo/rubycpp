#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "Sprite.h"
#include <map>

class Allocator
{
    public:
        Sprite* createSprite(int tag, int paletteTag, int tileTag);
        void createPalette(const char* paletteName, int tag);
        void createTile(const char* tileName, int tag);
        void destroySprite(int tag);
        void destroyPalette(int tag);
        Sprite* getSprite(int tag);
        int getPalette(int tag);
        int getTile(int tag);
        void destroyAllSprite();
        void destroyAllPalette();
    private:
        std::map<int, Sprite*> _sprite;
        std::map<int, int> _palette;
        std::map<int, int> _tile;
        int _spriteId = 0;
        int _paletteId = 0;
        int _tileId = 0;
};

extern Allocator allocator;

#endif
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "Sprite.h"
#include "SpriteGroup.h"

namespace Allocator
{
    namespace Sprite
    {
        ::Sprite* getByTag(int tag);
        void setByTag(int tag, ::Sprite* sprite);
        void eraseTag(int tag);
        ::Sprite* allocate();
        void deallocate(::Sprite* sprite);
    }
    namespace SpriteGroup
    {
        ::SpriteGroup* getByTag(int tag);
        void setByTag(int tag, ::SpriteGroup* group);
        void eraseTag(int tag);
    }
    namespace Matrix
    {
        int allocate();
        void deallocate(int matrixNum);
    }
    namespace Palette
    {
        int getByTag(int tag);
        void setByTag(int tag, int paletteNum);
        void eraseTag(int tag);
        int allocate(const char* tileName);
        void deallocate(int paletteNum);
    }
    namespace Tile
    {
        int getByTag(int tag);
        void setByTag(int tag, int tileNum);
        void eraseTag(int tag);
        int allocate(const char* tileName);
        void deallocate(int tileNum);
    }
}

#endif

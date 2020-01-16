#ifndef SPRITE_GROUP_H
#define SPRITE_GROUP_H

#include "Sprite.h"

#define GROUP_SIZE_MAX 20

enum GroupMode
{
    LINKED,
    OFFSET
};

class SpriteGroup : public Affine, public Updatable
{
    public:

        SpriteGroup() = default;
        SpriteGroup(int tag, bool insert_updater = true);
        ~SpriteGroup();

        void update();
        void add(Sprite* sprite);
        void activate();
        void deactivate();

        Sprite* sprite[GROUP_SIZE_MAX];
        int size = 0;
        GroupMode mode = GroupMode::LINKED;
};

#endif

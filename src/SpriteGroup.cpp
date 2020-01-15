#include "SpriteGroup.h"

#include "Allocator.h"
#include "Engine.h"

SpriteGroup::SpriteGroup(int tag, bool insert_updater): SpriteGroup()
{
    if(tag != -1)
        Allocator::SpriteGroup::setByTag(tag, this);
    if(insert_updater)
        Engine::updater.insert(this);
}

SpriteGroup::~SpriteGroup()
{
    for(int i = 0; i < size; ++i)
        delete sprite[i];
}

void SpriteGroup::update()
{
    switch(mode)
    {
        case GroupMode::UNLINKED:
            for(int i = 0; i < size; ++i)
                this->sprite[i]->update(this->pos1 + this->pos2);
            break;
        default:
            for(int i = 0; i < size; ++i)
            {
                this->sprite[i]->pos1 = this->pos1;
                this->sprite[i]->pos2 = this->pos2;
                this->sprite[i]->update();
            }
            break;
    }
}

void SpriteGroup::add(Sprite* sprite)
{
    if(size < GROUP_SIZE_MAX)
        this->sprite[size++] = sprite;
}

void SpriteGroup::activate()
{
    Updatable::activate();
    for(int i = 0; i < size; ++i)
        this->sprite[i]->activate();
}

void SpriteGroup::deactivate()
{
    Updatable::deactivate();
    for(int i = 0; i < size; ++i)
        this->sprite[i]->deactivate();
}

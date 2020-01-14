#include "SpriteGroup.h"

#include "Allocator.h"
#include "Engine.h"

SpriteGroup::SpriteGroup(int tag, bool insert_updater): SpriteGroup()
{
    if(tag != -1)
        Allocator::SpriteGroup::setByTag(tag, this);
    if(insert_updater)
    {
        this->active = false;
        Engine::updater.insert(this);
    }
}

SpriteGroup::~SpriteGroup()
{
    for(int i = 0; i < size; ++i)
        delete sprite[i];
}

void SpriteGroup::update()
{
    if(linked)
    {
        for(int i = 0; i < size; ++i)
        {
            this->sprite[i]->pos1 = this->pos1;
            this->sprite[i]->pos2 = this->pos2;
            this->sprite[i]->update();
        }
    }
    else
    {
        for(int i = 0; i < size; ++i)
        this->sprite[i]->update(this->pos1);
    }
}

void SpriteGroup::add(Sprite* sprite)
{
    if(size < GROUP_SIZE_MAX)
        this->sprite[size++] = sprite;
}

void SpriteGroup::activate()
{
    this->active = true;
    for(int i = 0; i < size; ++i)
        this->sprite[i]->active = true;
}

void SpriteGroup::deactivate()
{
    this->active = false;
    for(int i = 0; i < size; ++i)
        this->sprite[i]->active = false;
}

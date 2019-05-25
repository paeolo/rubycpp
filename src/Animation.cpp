#include "Allocator.h"
#include "Animation.h"

Animation::Animation(int spriteTag, int animTag)
{
    _spriteTag = spriteTag;
    _anim = anim[animTag];
}

void Animation::init()
{
    if(_spriteTag)
        this->sprite = allocator.getSprite(_spriteTag);
}

void Animation::routine()
{
    if(!_anim || _anim(this, _param))
        this->_end = true;
}

void Animation::preempt()
{
    this->_end = true;
}

bool Animation::end()
{
    return this->_end;
}
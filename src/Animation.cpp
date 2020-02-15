#include "Allocator.h"
#include "Animation.h"

Animation::Animation(int objectTag, int objectType, int animTag)
{
    _objectTag = objectTag;
    _objectType = objectType;
    _anim = anim[animTag];
}

Animation::~Animation()
{
    if (!this->_end)
    {
        if (_objectType != -1)
        {
            switch(_objectType)
            {
                case ObjectType::OBJECT_SPRITE:
                    delete object.sprite;
                    break;
                case ObjectType::OBJECT_SPRITE_GROUP:
                    delete object.group;
                    break;
            }      
        }
    }
}

void Animation::init()
{
    if (_objectTag != -1)
    {
        switch(_objectType)
        {
            case ObjectType::OBJECT_SPRITE:
                object.sprite = Allocator::Sprite::getByTag(_objectTag);
                break;
            case ObjectType::OBJECT_SPRITE_GROUP:
                object.group = Allocator::SpriteGroup::getByTag(_objectTag);
                break;
        }
    }
    if (parameter != -1)
        _param.rho = parameter;
}

void Animation::routine()
{
    if (_anim == nullptr || _anim(object, _param) == true)
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

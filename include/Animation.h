#ifndef ANIMATION_H
#define ANIMATION_H

#include "anim.h"
#include "Sprite.h"

enum ObjectType
{
    OBJECT_SPRITE,
    OBJECT_SPRITE_GROUP
};

class Animation
{
    public:
        Animation(int objectTag, int objectType, int animTag);
        void init();
        void routine();
        void preempt();
        bool end();

        anim_object_t object = anim_object_t();
        int parameter = -1;

        int delay = 0;
        bool endScene = false;
        Animation* previous = nullptr;
        Animation* next = nullptr;

    private:
        anim_t _anim = nullptr;
        anim_param_t _param = anim_param_t();
        int _objectTag = -1;
        int _objectType = -1;
        int _frame = 0;
        bool _end = false;
};

#endif
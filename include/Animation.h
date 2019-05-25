#ifndef ANIMATION_H
#define ANIMATION_H

#include "anim.h"
#include "Sprite.h"

class Animation
{
    public:
        Animation(int spriteTag, int animTag);
        void init();
        void routine();
        void preempt();
        bool end();

        Sprite* sprite = nullptr;
        Animation* previous = nullptr;
        Animation* next = nullptr;
        int delay = 0;

    private:
        anim_t _anim = nullptr;
        anim_param_t _param = anim_param_t();
        int _spriteTag = 0;
        int _frame = 0;
        bool _end = false;
};

#endif
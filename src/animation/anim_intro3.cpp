#include "Allocator.h"
#include "Animation.h"
#include "anim.h"
#include "Fixed.h"
#include "Palette.h"
#include "random.h"
#include "register.h"
#include "Sprite.h"
#include "trig.h"

bool anim_background_pokeball(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        LCD.DISPCNT |= DISPCNT::MODE_1;
        LCD.DISPCNT |= 1 << (8 + 2);
        param.init = true;
    }
    return true;
}

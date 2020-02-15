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
        param.init = true;
        return false;
    }
    return true;
}

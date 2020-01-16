#include "Allocator.h"
#include "Animation.h"
#include "anim.h"
#include "Fixed.h"
#include "Sprite.h"
#include "trig.h"
#include "register.h"

bool anim_background_scroll(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        param.count = 0;
        param.theta = 0;
        param.init = true;
    }

    BGOFS[1].x = param.count;
    BGOFS[1].y = 48 * Sin(param.theta & (127));
    ++param.theta;
    param.count -= 4;

    return false;
}

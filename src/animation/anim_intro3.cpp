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

        param.lambda[0] = 2;
        param.lambda[1] = 1;
        param.init = true;
    }
    
    BGAffineSource source;
    source.x = 0x8000;
    source.y = 0x8000;
    source.tX = 120;
    source.tY = 80;
    source.sX = 0x10000 / param.lambda[0];
    source.sY = 0x10000 / param.lambda[0];
    source.theta = param.rho;

    Background::AffineSet(source, AffineBG::BG_AFFINE_0);

    param.rho +=  0x400;
    param.lambda[0] += param.lambda[1];
    ++param.lambda[1];
    return false;
}

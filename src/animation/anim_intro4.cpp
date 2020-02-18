#include "Animation.h"
#include "anim.h"
#include "Fixed.h"
#include "Palette.h"
#include "random.h"
#include "register.h"
#include "Sprite.h"
#include "trig.h"

bool anim_plip_ploup(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        Palette::buffer[240] = BLANK;
        Palette::buffer[241] = RGB(31, 14, 12);
        Palette::buffer[242] = BLACK;
        Background::CreateTile4(ColorNumber::COLOR_0, 0, 0);
        Background::CreateTile4(ColorNumber::COLOR_1, 0, 1);
        Background::CreateTile4(ColorNumber::COLOR_2, 0, 2);
        param.init = true;
    }
    return true;
}

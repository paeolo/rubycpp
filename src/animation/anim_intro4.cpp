#include "Animation.h"
#include "anim.h"
#include "Fixed.h"
#include "Palette.h"
#include "random.h"
#include "register.h"
#include "Sprite.h"
#include "trig.h"

bool anim_background_red(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        Palette::buffer[240] = BLANK;
        Palette::buffer[241] = RGB(31, 14, 12);
        Palette::buffer[242] = BLACK;
        Background::CreateTile4(ColorNumber::COLOR_0, 0, 0);
        Background::CreateTile4(ColorNumber::COLOR_1, 0, 1);
        Background::CreateTile4(ColorNumber::COLOR_2, 0, 2);
        Background::CreateTileMap16(1, 15, 6, 0, 0x280);
        param.init = true;
        return false;
    }
    LCD.DISPCNT |= 1 << (8 + 2);
    return true;
}

bool anim_background_bands(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        Background::CreateTileMap16(2, 15, 7, 0, 0x80);
        Background::CreateTileMap16(0, 15, 7, 4, 0x180);
        Background::CreateTileMap16(2, 15, 7, 16, 0x80);
        LCD.WIN0H = 240;
        LCD.WIN0V = 160;
        LCD.DISPCNT |= DISPCNT::WIN0_ON;
        LCD.WININ |= WIN::WIN0_BG2
        | WIN::WIN0_BG3 
        | WIN::WIN0_OBJ;
        LCD.WINOUT = WIN::WIN0_BG0;
        LCD.DISPCNT |= 1 << (8 + 0);
        param.init = true;
    }
    
    LCD.WIN0V = (160 - 4*param.count) + ((4*param.count) << 8);

    if (param.count == 8)
        return true;
    ++param.count;
    return false;
}

bool anim_sharpedo(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        SPRITE->setShape(SQUARE, SIZE_64, AFFINE_DOUBLE);
        SPRITE->rotate(Fixed(1.0), Fixed(1.0), 0);
        SPRITE->pos1.x = 240;
        SPRITE->pos1.y = 160;
        SPRITE->activate();
        param.init = true;
    }
    if (param.count <= 15)
    {
        SPRITE->pos1.x -= 2;
        SPRITE->pos1.y -= 4;
    }
    else if (param.count >= 30)
    {
        SPRITE->pos2.y = - (param.rho * param.rho) >> 3;
        SPRITE->pos2.x -= param.rho;
        s16 i = 256 - param.lambda[0];
        SPRITE->rotate(Fixed::fromRaw(i), Fixed::fromRaw(i), 0);
        if (param.lambda[0] < 128)
            param.lambda[0]+= 8;
        ++param.rho;
    }
    if (SPRITE->pos2.x <= -300)
    {
        delete SPRITE;
        return true;
    }
    ++param.count;
    return false;
}

bool anim_duskull(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        SPRITE->setShape(SQUARE, SIZE_64, AFFINE_DOUBLE);
        SPRITE->rotate(Fixed(-1.0), Fixed(1.0), 0);
        SPRITE->pos1.x = 0;
        SPRITE->pos1.y = 160;
        SPRITE->activate();
        param.init = true;
    }
    if (param.count <= 15)
    {
        SPRITE->pos1.x += 2;
        SPRITE->pos1.y -= 4;
    }
    else if (param.count >= 30)
    {
        SPRITE->pos2.y = - (param.rho * param.rho) >> 3;
        SPRITE->pos2.x += param.rho;
        s16 i = 256 - param.lambda[0];
        SPRITE->rotate(Fixed::fromRaw(-i), Fixed::fromRaw(i), 0);
        if (param.lambda[0] < 128)
            param.lambda[0]+= 8;
        ++param.rho;
    }
    if (SPRITE->pos2.x >= 300)
    {
        delete SPRITE;
        return true;
    }
    ++param.count;
    return false;
}

#include "Animation.h"
#include "anim.h"
#include "Fixed.h"
#include "Palette.h"
#include "random.h"
#include "register.h"
#include "Sprite.h"
#include "trig.h"

#include "mgba.h"

static const CMDAnim may_launch[] =
    {
        CMD_FRAME(0, 0),
        CMD_FRAME(64, 8),
        CMD_FRAME(128, 0),
        CMD_END};

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
    LCD.DISPCNT |= 1 << (8 + 3);
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
        LCD.WININ |= WIN::WIN0_BG2 | WIN::WIN0_BG3 | WIN::WIN0_OBJ;
        LCD.WINOUT = WIN::WIN0_BG0;
        LCD.DISPCNT |= 1 << (8 + 0);
        param.init = true;
    }

    LCD.WIN0V = (160 - 4 * param.count) + ((4 * param.count) << 8);

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
        SPRITE->pos2.y = -(param.rho * param.rho) >> 3;
        SPRITE->pos2.x -= param.rho;
        s16 i = 256 - param.lambda[0];
        SPRITE->rotate(Fixed::fromRaw(i), Fixed::fromRaw(i), 0);
        if (param.lambda[0] < 128)
            param.lambda[0] += 8;
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
        SPRITE->pos2.y = -(param.rho * param.rho) >> 3;
        SPRITE->pos2.x += param.rho;
        s16 i = 256 - param.lambda[0];
        SPRITE->rotate(Fixed::fromRaw(-i), Fixed::fromRaw(i), 0);
        if (param.lambda[0] < 128)
            param.lambda[0] += 8;
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

bool anim_may_ready(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        SPRITE->setShape(SQUARE, SIZE_64, AFFINE_DISABLE);
        SPRITE->pos1.x = 280;
        SPRITE->pos1.y = 96;
        SPRITE->activate();
        Palette::buffer[241] = RGB(22, 31, 15);
        param.init = true;
    }
    SPRITE->pos2.x -= 4;

    if (SPRITE->pos2.x <= -240)
    {
        SPRITE->tileOffset = 0;
        return true;
    }
    ++param.count;
    return false;
}

bool anim_pokeball_appear(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        GROUP->mode = GroupMode::OFFSET;
        GROUP->sprite[0]->setShape(SQUARE, SIZE_16, AFFINE_ENABLE);
        GROUP->sprite[1]->setShape(SQUARE, SIZE_16, AFFINE_ENABLE);
        GROUP->sprite[0]->rotate(Fixed(1.0), Fixed(1.0), 0);
        GROUP->sprite[1]->rotate(Fixed(1.0), Fixed(1.0), 0);
        GROUP->activate();
        return true;
    }
}

bool anim_may_launch(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        SPRITE->start(may_launch);
        param.init = true;
        return false;
    }
    if (SPRITE->pos2.y <= 50)
    {
        --SPRITE->pos2.x;
        SPRITE->pos2.y += 2;
    }
    else
    {
        delete SPRITE;
        return true;
    }
    return false;
}

bool anim_background_streaks(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        for (int i = 0; i < 0x10; ++i)
            Palette::data[i] = Palette::buffer[i];

        param.rho = 9;
        param.count = 0;
        param.lambda[0] = 0;

        BGOFS[2].x = 0;
        BGOFS[2].y = 0;
        LCD.DISPCNT |= 1 << (8 + 2);
        param.init = true;
    }

    if ((param.count & 7) == 0)
    {
        --param.rho;
        for (int i = 0; i < 0x10; ++i)
            Palette::buffer[i] = Color::centroid(
                RGB(23, 31, 13),
                Palette::data[i],
                (param.rho << 2));
    }

    BGOFS[2].x = param.lambda[0];
    BGOFS[2].y = -param.lambda[0];
    param.lambda[0] += param.rho;

    if (param.rho == 0)
        return true;

    ++param.count;
    return false;
}

bool anim_pokeball_launch(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        param.rho = 36;
        param.init = true;
    }

    if (param.rho != 0)
    {
        if (GROUP->pos1.x <= 104)
        {
            GROUP->pos1.x += 3;
            GROUP->pos1.y -= 1;
            ++GROUP->sprite[0]->pos1.x;
            if ((param.count & 5) == 0)
                ++GROUP->sprite[0]->pos1.x;
            if ((param.count & 7) == 0)
                ++GROUP->sprite[0]->pos1.y;
            GROUP->pos2.y = -24 * Sin(param.theta);
        }

        GROUP->sprite[0]->rotate(Fixed(1.0), Fixed(1.0), param.alpha);
        GROUP->sprite[1]->rotate(Fixed(1.0), Fixed(1.0), param.alpha);
        param.alpha += param.rho;
        param.theta += 4;

        if ((param.count & 1) == 0)
            --param.rho;
    }

    if (param.rho == 0)
    {
        delete GROUP;
        return true;
    }

    ++param.count;
    return false;
}

bool anim_pokeball_stars(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        for (int i = 0; i < 8; ++i)
            GROUP->sprite[i]->setShape(SQUARE, SIZE_8, AFFINE_DISABLE);

        GROUP->mode = GroupMode::OFFSET;
        GROUP->activate();
        param.init = true;
    }
    return true;
}

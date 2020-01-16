#include "Allocator.h"
#include "Animation.h"
#include "anim.h"
#include "Fixed.h"
#include "Sprite.h"
#include "trig.h"
#include "register.h"

static const u16 alpha_blend[32] =
{
    16, 272, 528, 784, 1040, 1296, 1552, 1808, 2064,
    2320, 2576, 2832, 3088, 3344, 3600, 3856, 4111,
    4110, 4109, 4108, 4107, 4106, 4105, 4104, 4103,
    4102, 4101, 4100, 4099, 4098, 4097, 4096
};

bool anim_waterdrop_fly(anim_object_t &object, anim_param_t &param)
{
    if(!param.init)
    {
        GROUP->activate();
        GROUP->sprite[0]->setShape(SQUARE, SIZE_32, AFFINE_DOUBLE);
        GROUP->sprite[1]->setShape(SQUARE, SIZE_32, AFFINE_DOUBLE);
        GROUP->sprite[2]->setShape(SQUARE, SIZE_32, AFFINE_DOUBLE);
        param.init = true;
    } 
    GROUP->pos1.x--;
    GROUP->pos2.y = 8 * Sin(param.theta);
    
    if (GROUP->pos1.x & 1)
        GROUP->pos1.y++;
            
    int alpha = - 16 * (Cos(param.theta) + Fixed(1));

    GROUP->sprite[0]->scale(2.0, 2.0);
    GROUP->sprite[1]->rotate(2.0, 2.0, alpha);
    GROUP->sprite[2]->rotate(2.0, 4.0, alpha);
    
    param.theta += 2;
    return false;
}

bool anim_waterdrop_stay(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        GROUP->pos1.x += 1;
        GROUP->pos1.y += GROUP->pos2.y;
        GROUP->pos2.y = 0;

        GROUP->sprite[0]->scale(2.25, 2.25);
        GROUP->sprite[1]->scale(2.25, 2.25);
        GROUP->sprite[2]->scale(2.25, 2.25);

        param.theta = 128;
        param.alpha = 0;
        param.init = true;
    }
    else if (param.theta != 64)
    {
        param.theta -= 8;
        GROUP->pos2.x = 4 + 4 * Cos(param.theta);
        GROUP->pos2.y = 4 * Sin(param.theta);
    }
    else
    {
        param.alpha += 8;
        int theta = 16 * Sin(param.alpha) + 64;
        GROUP->pos2.x = 4 + 4 * Cos(theta);
        GROUP->pos2.y = 4 * Sin(theta);
    }
    return false;
}

bool anim_waterdrop_fall(anim_object_t &object, anim_param_t &param)
{
    if(GROUP->pos1.y <= 120)
    {
        GROUP->pos1.y += 4;
        return false;
    }
    else
    {
        GROUP->pos1.y += 2;
        GROUP->sprite[0]->visible = false;
        GROUP->sprite[1]->visible = false;
        GROUP->sprite[2]->visible = false;
        return true;
    }
}

bool anim_waterdrop_fall_immediately(anim_object_t &object, anim_param_t &param)
{
    if(!param.init)
    {
        GROUP->activate();
        GROUP->sprite[0]->setShape(SQUARE, SIZE_32, AFFINE_DOUBLE);
        GROUP->sprite[1]->setShape(SQUARE, SIZE_32, AFFINE_DOUBLE);
        GROUP->sprite[2]->setShape(SQUARE, SIZE_32, AFFINE_DOUBLE);

        GROUP->sprite[0]->scale(4.125, 4.125);
        GROUP->sprite[1]->scale(4.125, 4.125);
        GROUP->sprite[2]->scale(4.125, 8.250);

        param.rho = (GROUP->pos1.x >= 120) ? 120 : 120 - (120 - GROUP->pos1.x) * Fixed(0.125);
        param.init = true;
        return false;
    }

    if(GROUP->pos1.y <= param.rho)
    {
        GROUP->pos1.y += 4;
        return false;
    }
    else
    {
        GROUP->pos1.y += 2;
        GROUP->sprite[0]->visible = false;
        GROUP->sprite[1]->visible = false;
        GROUP->sprite[2]->visible = false;
        return true;
    }
}

bool anim_waterdrop_splash(anim_object_t &object, anim_param_t &param)
{
    Sprite* sprite = GROUP->sprite[param.rho];
    if(!param.init)
    {
        sprite->tileOffset = 48;
        sprite->setShape(HORIZONTAL, SIZE_64, AFFINE_DOUBLE);

        param.count = 6;
        param.gamma = Fixed(4.0);
        param.init = true;
        return false;
    }

    if (param.count > 0)
    {
        --param.count;
    }
    else if (param.gamma >= Fixed(0.75))
    {
        if(!sprite->visible)
            sprite->visible = true;

        int palette = 9 + 2*(param.gamma - Fixed(0.75));

        sprite->scale(param.gamma, param.gamma);
        sprite->entry.paletteNum = (palette > 15) ? 15 : palette;
        param.gamma = Fixed(0.95) * param.gamma;
    }
    else
    {
        if(param.rho != 2)
            sprite->visible = false;
        else
            delete GROUP;
            
        return true;
    }
    return false;
}

bool anim_gamefreak_logo_appear(anim_object_t &object, anim_param_t &param)
{
    if(!param.init)
    {
        LCD.BLDCNT = EFFECT_BLEND | TP1_OBJ | TP2_ALL;
        LCD.BLDALPHA = alpha_blend[64];
        LCD.BLDY = 0;

        GROUP->mode = GroupMode::OFFSET;
        GROUP->activate();
        
        for (int i = 0; i < 18; i++)
        {
            if (i < 9)
                GROUP->sprite[i]->setShape(SQUARE, SIZE_16, AFFINE_DISABLE);
            else if (i < 17)
                GROUP->sprite[i]->setShape(SQUARE, SIZE_8, AFFINE_DISABLE);
            else if (i == 17)
                GROUP->sprite[i]->setShape(VERTICAL, SIZE_64, AFFINE_DISABLE);
        }
        param.count = 64;
        param.init = true;
    }
    if (param.count > 0)
    {
        --param.count;
        LCD.BLDALPHA = alpha_blend[param.count >> 1];
    }
    else
        return true;

    return false;
}

bool anim_gamefreak_logo_disappear(anim_object_t &object, anim_param_t &param)
{
    if(!param.init)
    {
        param.count = 0;
        param.init = true;
    }

    if(param.count <= 64)
    {
        if(param.count < 64)
            LCD.BLDALPHA = alpha_blend[param.count >> 1];
        else
            delete GROUP;
        ++param.count;
    }
    else
    {
        LCD.BLDCNT = EFFECT_NONE;
        LCD.BLDALPHA = 0;
        LCD.BLDY = 0;
        return true;
    }
    return false;
}

bool anim_scroll_down(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        param.rho = 0;
        param.gamma = Fixed(4096.0/160.0);
        param.init = true;
    }
    else if(param.rho <= 160)
    {
        BGOFS[2].y = ((80*(160 - param.rho) - 43*param.rho)* param.gamma) >> 12; 
        BGOFS[1].y = ((24*(160 - param.rho) - 139*param.rho)* param.gamma) >> 12; 
        BGOFS[0].y = ((40*(160 - param.rho) - 205*param.rho)* param.gamma) >> 12;
        ++param.rho;
    }
    else
        return true;
        
    return false;
}

bool anim_latios_flight(anim_object_t &object, anim_param_t &param)
{
    ++param.count;
    if(!param.init)
    {
        SPRITE->activate();
        SPRITE->setShape(HORIZONTAL, SIZE_64, AFFINE_DOUBLE);

        param.alpha = -24;
        param.gamma = 0.5;
        param.init = true;
    }
    else if (param.theta < 80)
    {
        SPRITE->pos2.x = - 140 * Sin(param.theta);
        SPRITE->pos2.y = - 120 * Sin(param.theta);
        if(param.theta > 64)
            SPRITE->entry.priority = 3;
    }

    SPRITE->rotate(param.gamma, param.gamma, param.alpha);

    param.gamma += (param.gamma < Fixed(1.0)) ? Fixed(1/32.0) : Fixed(1/8.0);
    param.alpha += (param.alpha < 24) ? 1 : 0;

    if(param.theta < 64)
        param.theta += 2;
    else if(!(param.count & 3))
        param.theta += 1;
    
    if(param.gamma >= Fixed(16.0))
    {
        delete SPRITE;
        return true;
    }
    return false;
}

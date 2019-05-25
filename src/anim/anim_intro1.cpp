#include "Allocator.h"
#include "Animation.h"
#include "anim.h"
#include "Fixed.h"
#include "Sprite.h"
#include "trig.h"
#include "register.h"

#define sprite animation->sprite

bool anim_waterdrop_fly(Animation* animation, anim_param_t &param)
{
    if(!param.init)
    {
        sprite->setShape(SQUARE, SIZE_32, AFFINE_DOUBLE);
        sprite->child[0]->setShape(SQUARE, SIZE_32, AFFINE_DOUBLE);
        sprite->child[1]->setShape(SQUARE, SIZE_32, AFFINE_DOUBLE);
        param.init = true;
    } 

    sprite->pos1.x--;
    sprite->pos2.y = 8 * Sin(param.theta);
    
    if (sprite->pos1.x & 1)
        sprite->pos1.y++;
            
    int alpha = - 16 * Cos(param.theta) - 16;

    sprite->scale(2.0, 2.0);
    sprite->child[0]->rotate(2.0, 2.0, alpha);
    sprite->child[1]->rotate(2.0, 4.0, alpha);
    
    param.theta += 2;

    sprite->update();
    return false;
}

bool anim_waterdrop_stay(Animation* animation, anim_param_t &param)
{
    if (!param.init)
    {
        sprite->pos1.x += 1;
        sprite->pos1.y += sprite->pos2.y;
        sprite->pos2.y = 0;

        sprite->scale(2.25, 2.25);
        sprite->child[0]->scale(2.25, 2.25);
        sprite->child[1]->scale(2.25, 2.25);

        param.theta = 128;
        param.alpha = 0;
        param.init = true;
    }
    else if (param.theta != 64)
    {
        param.theta -= 8;
        sprite->pos2.x = 4 + 4 * Cos(param.theta);
        sprite->pos2.y = 4 * Sin(param.theta);
    }
    else
    {
        param.alpha += 8;
        int theta = 16 * Sin(param.alpha) + 64;
        sprite->pos2.x = 4 + 4 * Cos(theta);
        sprite->pos2.y = 4 * Sin(theta);
    }

    sprite->update();
    return false;
}

bool anim_waterdrop_fall(Animation* animation, anim_param_t &param)
{
    if(sprite->pos1.y <= 120)
    {
        sprite->pos1.y += 4;
        sprite->update();
        return false;
    }
    else
    {
        sprite->visible = false;
        sprite->child[0]->visible = false;
        sprite->child[1]->visible = false;
        sprite->update();
        sprite->child[0] = nullptr;
        sprite->child[1] = nullptr;
        return true;
    }
}

bool anim_waterdrop_fall_immediatly(Animation* animation, anim_param_t &param)
{
    if(!param.init)
    {
        sprite->setShape(SQUARE, SIZE_32, AFFINE_DOUBLE);
        sprite->child[0]->setShape(SQUARE, SIZE_32, AFFINE_DOUBLE);
        sprite->child[1]->setShape(SQUARE, SIZE_32, AFFINE_DOUBLE);

        sprite->scale(4.125, 4.125);
        sprite->child[0]->scale(4.125, 4.125);
        sprite->child[1]->scale(4.125, 8.250);

        param.rho = (sprite->pos1.x >= 120) ? 120 : 120 - (120 - sprite->pos1.x) * Fixed(0.125);
        param.init = true;

        return false;
    }

    if(sprite->pos1.y <= param.rho)
    {
        sprite->pos1.y += 4;
        sprite->update();
        return false;
    }
    else
    {
        sprite->visible = false;
        sprite->child[0]->visible = false;
        sprite->child[1]->visible = false;
        sprite->update();
        sprite->child[0] = nullptr;
        sprite->child[1] = nullptr;
        return true;
    }
}

bool anim_waterdrop_splash(Animation* animation, anim_param_t &param)
{
    if(!param.init)
    {
        sprite->pos1.y += 2;
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
    else if (param.gamma > Fixed(0.75))
    {
        if(!sprite->visible)
            sprite->visible = true;

        sprite->scale(param.gamma, param.gamma);
        param.gamma = Fixed(0.95) * param.gamma;
        int palette = 9 + 2*(param.gamma - Fixed(0.75));
        sprite->entry.paletteNum = (palette > 15) ? 15 : palette;
    }
    else
    {
        sprite->destroy();
        return true;
    }

    sprite->update();
    return false;
}

bool anim_gamefreak_logo(Animation* animation, anim_param_t &param)
{
    static const s16 game_table[9][2] =
    {
        {80, -72}, {84, -56}, {88, -40}, {92, -24},
        {96, 8}, {100, 24}, {92, 40}, {84, 56}, {104, 72},
    };

    static const s16 freak_table[8][2] =
    { 
        {112, -28}, {113, -20}, {114, -12}, {115, -4},
        {114, 4}, {116, 12}, {117, 20}, {115, 28},
    };

    static const u16 alpha_blend[32] =
    {
        16, 272, 528, 784, 1040, 1296, 1552, 1808, 2064,
        2320, 2576, 2832, 3088, 3344, 3600, 3856, 4111,
        4110, 4109, 4108, 4107, 4106, 4105, 4104, 4103,
        4102, 4101, 4100, 4099, 4098, 4097, 4096
    };

    if(!param.init)
    {
        LCD.BLDCNT = EFFECT_BLEND | TP1_OBJ | TP2_ALL;
        LCD.BLDALPHA = alpha_blend[64];
        LCD.BLDY = 0;

        Sprite* object;
        for (int i = 0; i < 9; i++)
        {
            object = allocator.createSprite(200 + i, 101, 100);
            object->setShape(SQUARE, SIZE_16, AFFINE_DISABLE);
            object->tileOffset = game_table[i][0];
            object->pos1.x = 120 + game_table[i][1];
            object->pos1.y = 76;
            object->update();
        }
        for (int i = 0; i < 8; i++)
        {
            object = allocator.createSprite(209 + i, 101, 100);
            object->setShape(SQUARE, SIZE_8, AFFINE_DISABLE);
            object->tileOffset = freak_table[i][0];
            object->pos1.x = 120 + freak_table[i][1];
            object->pos1.y = 92;
            object->update();
        }

        object = allocator.createSprite(217, 101, 100);
        object->setShape(VERTICAL, SIZE_64, AFFINE_DISABLE);
        object->tileOffset = 128;
        object->pos1.x = 120;
        object->pos1.y = 76;
        object->update();

        param.count = 64;
        param.lambda[0] = 64;
        param.lambda[1] = 0;
        param.init = true;
    }

    if (param.lambda[0] > 0)
    {
        --param.lambda[0];
        LCD.BLDALPHA = alpha_blend[param.lambda[0]  >> 1];
    }
    else if (param.count > 0)
    {
        --param.count;
    }
    else if(param.lambda[1] <= 64)
    {
        if(param.lambda[1] < 64)
            LCD.BLDALPHA = alpha_blend[param.lambda[1] >> 1];
        else
        {
            for (int i = 0; i < 18; i++)
                allocator.destroySprite(200 + i);
        }
        ++param.lambda[1];
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

bool anim_scroll_down(Animation* animation, anim_param_t &param)
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
    {
        return true;
    }
    return false;
}

bool anim_latios_flight(Animation* animation, anim_param_t &param)
{
    ++param.count;
    if(!param.init)
    {
        sprite->setShape(HORIZONTAL, SIZE_64, AFFINE_DOUBLE);

        param.alpha = -24;
        param.gamma = 0.5;
        param.init = true;
    }
    else if (param.theta < 80)
    {
        sprite->pos2.x = - 140 * Sin(param.theta);
        sprite->pos2.y = - 120 * Sin(param.theta);
        if(param.theta > 64)
            sprite->entry.priority = 3;
    }

    sprite->rotate(param.gamma, param.gamma, param.alpha);

    param.gamma += (param.gamma < Fixed(1.0)) ? Fixed(1/32.0) : Fixed(1/8.0);
    param.alpha += (param.alpha < 24) ? 1 : 0;

    if(param.theta < 64)
        param.theta += 2;
    else if(!(param.count & 3))
        param.theta += 1;
    
    if(param.gamma >= Fixed(16.0))
    {
        sprite->destroy();
        return true;
    }
    sprite->update();
    return false;
}
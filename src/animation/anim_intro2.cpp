#include "Allocator.h"
#include "Animation.h"
#include "anim.h"
#include "Fixed.h"
#include "Sprite.h"
#include "trig.h"
#include "register.h"

#include "mgba.h"

static int bg_y_pos = 0;

inline void update_bg_y_pos(s8 &theta, unsigned int &count, int &rho)
{
    if (rho < 2)
    {
        if ((count & 3) == 0)
        {
            theta = (theta + 1) & 127;
            if (theta == 0)
                ++rho;
        }
        bg_y_pos = 48 * Sin(theta);
    }
}

bool anim_background_scroll(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        param.theta = 92;
        param.count = 3;
        param.init = true;
    }
    BGOFS[1].x = -4 * param.count;
    BGOFS[3].x = -(param.count >> 2);

    update_bg_y_pos(param.theta, param.count, param.rho);
    BGOFS[1].y = bg_y_pos;
    BGOFS[3].y = bg_y_pos;
    ++param.count;
    return false;
}

bool anim_trees_group_1(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        GROUP->activate();
        GROUP->mode = GroupMode::OFFSET;
        for (int i = 0; i < 4; ++i)
            GROUP->sprite[i]->setShape(SQUARE, SIZE_32, AFFINE_DISABLE);
        param.theta = 92;
        param.lambda[0] = GROUP->pos1.x;
        param.lambda[1] = GROUP->pos1.y;
        param.init = true;
    }
    GROUP->pos1.x = param.lambda[0] + (param.count >> 3);
    GROUP->pos1.y = param.lambda[1] - bg_y_pos;
    ++param.count;
    return false;
}

bool anim_trees_group_2(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        GROUP->activate();
        GROUP->mode = GroupMode::OFFSET;
        for (int i = 0; i < 4; ++i)
            GROUP->sprite[i]->setShape(VERTICAL, SIZE_32, AFFINE_DISABLE);
        param.theta = 92;
        param.lambda[0] = GROUP->pos1.x;
        param.lambda[1] = GROUP->pos1.y;
        param.init = true;
    }
    GROUP->pos1.x = param.lambda[0] + (param.count >> 4);
    GROUP->pos1.y = param.lambda[1] - bg_y_pos;
    ++param.count;
    return false;
}

bool anim_trees_group_3(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        GROUP->activate();
        GROUP->mode = GroupMode::OFFSET;
        for (int i = 0; i < 4; ++i)
            GROUP->sprite[i]->setShape(VERTICAL, SIZE_32, AFFINE_DISABLE);
        param.theta = 92;
        param.lambda[0] = GROUP->pos1.x;
        param.lambda[1] = GROUP->pos1.y;
        param.init = true;
    }
    GROUP->pos1.x = param.lambda[0] + (param.count >> 5);
    GROUP->pos1.y = param.lambda[1] - bg_y_pos;
    ++param.count;
    return false;
}

bool anim_may(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        GROUP->activate();
        GROUP->mode = GroupMode::OFFSET;
        GROUP->sprite[0]->setShape(SQUARE, SIZE_64, AFFINE_DISABLE);
        GROUP->sprite[1]->setShape(HORIZONTAL, SIZE_64, AFFINE_DISABLE);
        param.init = true;
    }
    return false;
}

bool anim_latios(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        GROUP->activate();
        GROUP->mode = GroupMode::OFFSET;
        GROUP->sprite[0]->setShape(SQUARE, SIZE_64, AFFINE_DISABLE);
        GROUP->sprite[1]->setShape(SQUARE, SIZE_64, AFFINE_DISABLE);
        param.theta = 176;
        param.init = true;
    }
    if (param.count == 0)
    {
        GROUP->pos2.x += 8;
        if (GROUP->pos2.x >= 400)
            param.count = 1;
    }
    else if (param.count == 1)
    {
        GROUP->pos2.x -= 1;
        if (GROUP->pos2.x <= 216)
            param.count = 2;
    }
    else if (param.count == 2)
    {
        GROUP->pos2.x -= 2;
        if (GROUP->pos2.x <= 0)
        {
            delete GROUP;
            return true;
        }
    }
    param.theta += 4;
    GROUP->pos2.y = 8 * Sin(param.theta) - bg_y_pos;
    return false;
}

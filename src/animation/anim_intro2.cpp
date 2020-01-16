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
        param.theta = 92;
        param.count = 3;
        param.init = true;
    }
    BGOFS[1].x = -4 * param.count;
    BGOFS[3].x = -( param.count >> 2);

    if (param.rho < 2)
    {
        if ((param.count & 3) == 0)
        {
            param.theta = (param.theta + 1) & 127;
            if (param.theta == 0)
                ++param.rho;
        }
        BGOFS[1].y = 48 * Sin(param.theta);
        BGOFS[3].y = 48 * Sin(param.theta);
    }
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
    if (param.rho < 2)
    {
        if ((param.count & 3) == 0)
        {
            param.theta = (param.theta + 1) & 127;
            if (param.theta == 0)
                ++param.rho;
        }
        GROUP->pos1.y = param.lambda[1] - 48 * Sin(param.theta);
    }
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
    if (param.rho < 2)
    {
        if ((param.count & 3) == 0)
        {
            param.theta = (param.theta + 1) & 127;
            if (param.theta == 0)
                ++param.rho;
        }
        GROUP->pos1.y = param.lambda[1] - 48 * Sin(param.theta);
    }
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
    if (param.rho < 2)
    {
        if ((param.count & 3) == 0)
        {
            param.theta = (param.theta + 1) & 127;
            if (param.theta == 0)
                ++param.rho;
        }
        GROUP->pos1.y = param.lambda[1] - 48 * Sin(param.theta);
    }
    ++param.count;
    return false;
}

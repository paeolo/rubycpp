#include "Allocator.h"
#include "Animation.h"
#include "anim.h"
#include "Fixed.h"
#include "Palette.h"
#include "random.h"
#include "register.h"
#include "Sprite.h"
#include "trig.h"

static const CMDAnim treadle_bike[] =
{
    CMD_FRAME(0, 8),
    CMD_FRAME(32, 8),
    CMD_FRAME(64, 8),
    CMD_FRAME(96, 8),
    CMD_JUMP(0)
};
static const CMDAnim treadle_may[] =
{
    CMD_FRAME(0, 4),
    CMD_FRAME(64, 4),
    CMD_FRAME(128, 4),
    CMD_FRAME(192, 4),
    CMD_JUMP(0)
};

static const CMDAnim may_see_latios_1[] =
{
    CMD_FRAME(256, 4),
    CMD_FRAME(320, 4),
    CMD_FRAME(384, 4),
    CMD_END
};

static const CMDAnim may_see_latios_2[] =
{
    CMD_FRAME(384, 16),
    CMD_FRAME(320, 16),
    CMD_FRAME(256, 16),
    CMD_END
};

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

inline void update_may_y_pos(int &y, unsigned int &count)
{
    if ((count & 7) == 0)
    {
        if (y != 0)
            y = 0;
        else
        {
            int rand = Random() & 3;
            if (rand == 0)
                y = -1;
            else if (rand == 1)
                y = 1;
            else
                y = 0;
        }
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

bool anim_may_begin(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        GROUP->activate();
        GROUP->mode = GroupMode::OFFSET;
        GROUP->sprite[0]->setShape(SQUARE, SIZE_64, AFFINE_DISABLE);
        GROUP->sprite[1]->setShape(HORIZONTAL, SIZE_64, AFFINE_DISABLE);
        GROUP->sprite[0]->start(treadle_may);
        GROUP->sprite[1]->start(treadle_bike);
        param.init = true;
    }
    if (param.count <= 80)
        --GROUP->pos2.x;
    else if ((param.count & 7) == 0)
        ++GROUP->pos2.x;
    update_may_y_pos(GROUP->pos2.y, param.count);
    ++param.count;
    return false;
}

bool anim_may_bike(anim_object_t &object, anim_param_t &param)
{
    --GROUP->pos2.x;
    update_may_y_pos(GROUP->pos2.y, param.count);
    ++param.count;
    return false;
}

bool anim_may_see_latios(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        GROUP->sprite[0]->start(may_see_latios_1);
        param.init = true;
    }
    if (GROUP->pos2.x <= -80)
    {
        ++GROUP->pos2.x;
        update_may_y_pos(GROUP->pos2.y, param.count);
    }
    else
    {
        GROUP->sprite[0]->start(may_see_latios_2);
        return true;
    }
    ++param.count;
    return false;
}

bool anim_may_bike_fast(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        GROUP->sprite[0]->start(treadle_may);
        param.init = true;
    }
    GROUP->pos2.x -= 2;
    update_may_y_pos(GROUP->pos2.y, param.count);
    ++param.count;
    if (GROUP->pos2.x <= -300)
    {
        delete GROUP;
        return true;
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

bool anim_fade(anim_object_t &object, anim_param_t &param)
{
    if (!param.init)
    {
        for (int i= 0; i < 0x200; ++i)
            Palette::data[i] = Palette::buffer[i];

        param.rho = 0;
        param.count = 0;
        param.init = true;
    }
    if (param.count % 20 == 0)
    {
        ++param.rho;
        for (int i= 0; i < 0x200; ++i)
            Palette::buffer[i] = Color::centroid(Palette::data[i], BLANK, (param.rho << 2));
    }
    if (param.rho == 8)
        return true;

    ++param.count;
    return false;
}

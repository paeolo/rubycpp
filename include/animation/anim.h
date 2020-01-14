#ifndef ANIM_JUMP_TABLE_H
#define ANIM_JUMP_TABLE_H

#define TAG(n) bool
#define SPRITE object.sprite
#define GROUP object.group

#include "Fixed.h"
#include "Sprite.h"
#include "SpriteGroup.h"

typedef union anim_object
{
    Sprite* sprite;
    SpriteGroup* group;

} anim_object_t;

typedef struct anim_param
{
    bool init;
    s8 alpha;
    s8 theta;
    unsigned int count;
    int rho;
    int lambda[2];
    Fixed gamma;

} anim_param_t;

class Animation;

typedef bool (*anim_t)(anim_object_t &object, anim_param_t &param);
extern const anim_t anim[];

#endif

#ifndef ANIM_JUMP_TABLE_H
#define ANIM_JUMP_TABLE_H

#define TAG(n) bool

#include "Fixed.h"

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

typedef bool (*anim_t)(Animation* animation, anim_param_t &param);
extern const anim_t anim[];

#endif
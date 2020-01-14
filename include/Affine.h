#ifndef AFFINE_H
#define AFFINE_H

#include "Fixed.h"

typedef struct pos
{
    int x;
    int y;
} pos_t;

class Affine
{
    public:
        Affine() = default;
        virtual ~Affine() = default;

        pos_t pos1 = pos_t();
        pos_t pos2 = pos_t();
        bool visible = true;
};

#endif

#ifndef AFFINE_OBJECT_H
#define AFFINE_OBJECT_H

#include "Fixed.h"

#define CHILD_LENGTH 2

typedef struct pos
{
    int x;
    int y;
} pos_t;

class AffineObject
{
    public:
        AffineObject() = default;
        virtual ~AffineObject() = default;

        pos_t pos1 = pos_t();
        pos_t pos2 = pos_t();
        bool visible = true;

        virtual void update();
        virtual void scale(Fixed a, Fixed b) = 0;
        virtual void rotate(Fixed a, Fixed b, int theta) = 0;
        virtual void setShape(int shape, int size, int mode) = 0;

        void addChild(AffineObject* object);
        AffineObject* child[CHILD_LENGTH] = {nullptr};

    private:
        int _length = 0;

};

#endif
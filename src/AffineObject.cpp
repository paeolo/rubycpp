#include "AffineObject.h"

void AffineObject::update()
{
    for(int i = 0; i < CHILD_LENGTH; ++i)
    {
        if(this->child[i])
        {
            child[i]->pos1 = this->pos1;
            child[i]->pos2 = this->pos2;
            child[i]->update();
        }
    }
}

void AffineObject::addChild(AffineObject* object)
{
    if(_length < CHILD_LENGTH)
    {
        this->child[_length ] = object;
        ++_length;
    }
}
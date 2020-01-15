#ifndef SPRITE_SORTER_H
#define SPRITE_SORTER_H

#include "Sortable.h"
#include <list>

class SpriteSorter
{
    public:
        void insert(Sortable* sortable);
        void sort();

    private:
        std::list<Sortable*> _list;
		int _listSize = 0;
};

#endif

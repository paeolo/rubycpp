#ifndef SORTER_H
#define SORTER_H

#include "Sortable.h"
#include <list>

class Sorter
{
    public:
        void insert(Sortable* sortable);
        void sort();

    private:
        std::list<Sortable*> _list;
		int _listSize = 0;
};

#endif

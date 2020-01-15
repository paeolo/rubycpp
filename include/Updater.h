#ifndef UPDATER_H
#define UPDATER_H

#include "Updatable.h"
#include <list>

class Updater
{
    public:
        void insert(Updatable* updatable);
        void update();

    private:
        std::list<Updatable*> _list;
};

#endif

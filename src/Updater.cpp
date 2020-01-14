#include "Updater.h"

void Updater::insert(Updatable* updatable)
{
    std::list<Updatable*>::iterator it;
    it = _list.insert(_list.end(), updatable);
    (*it)->_holder = &*it;
}

void Updater::update()
{
    std::list<Updatable*>::iterator it;
    for(it = _list.begin(); it != _list.end(); ++it)
    {
        while(it != _list.end() && *it == nullptr)
            it = _list.erase(it);

        if(it != _list.end() && (*it)->active)
            (*it)->update();
    }
}

void Updater::clear()
{
    _list.clear();
}

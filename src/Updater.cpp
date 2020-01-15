#include "Updater.h"

void Updater::insert(Updatable* updatable)
{
    std::list<Updatable*>::iterator it = _list.end();
    it = _list.insert(it, updatable);
    updatable->_holder = &*it;
}

void Updater::update()
{
    std::list<Updatable*>::iterator it = _list.begin();
    while (it != _list.end())
    {
        if ((*it) != nullptr)
        {
            if ((*it)->_active)
                (*it)->update();
        }
        else
            it = _list.erase(it);
        ++it;
    }
}

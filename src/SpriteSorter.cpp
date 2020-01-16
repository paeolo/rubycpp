#include "SpriteSorter.h"
#include "Sprite.h"

void SpriteSorter::insert(Sortable *sortable)
{
    std::list<Sortable *>::iterator it = _list.begin();
    for (; it != _list.end(); ++it)
    {
        if (sortable->_priority < (*it)->_priority)
            break;
    }
    it = _list.insert(it, sortable);
    sortable->_holder = &*it;
}

void SpriteSorter::sort()
{
    int id = 0;
    std::list<Sortable *>::iterator it = _list.begin();
    while (it != _list.end())
    {
        if (*it != nullptr)
        {
            if((*it)->_id != id && !(*it)->_active)
            {
                ObjectEntry entry = Sprite::buffer.Object[(*it)->_id];
                entry.coefficient = Sprite::buffer.Object[id].coefficient;
                Sprite::buffer.Object[id] = entry;
            }
            (*it)->_id = id;
            ++id;
            ++it;
        }
        else 
            it = _list.erase(it);
    }
    for (int i = id; i < _listSize; ++i)
    {
        ObjectEntry entry = Sprite::emptyEntry;
        entry.coefficient = Sprite::buffer.Object[i].coefficient;
        Sprite::buffer.Object[i] = entry;
    }
    _listSize = id;
}

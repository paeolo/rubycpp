#include "SpriteSorter.h"
#include "Sprite.h"

void SpriteSorter::insert(Sortable *sortable)
{
    int id = _list.size();
    std::list<Sortable *>::iterator it = _list.begin();
    for (; it != _list.end(); ++it)
    {
        if (sortable->priority <= (*it)->priority)
            break;
        --id;
    }
    it = _list.insert(it, sortable);
    sortable->_id = id;
    sortable->_holder = &*it;
}

void SpriteSorter::sort()
{
    int id = 0;
    std::list<Sortable *>::iterator it = _list.end();
    while (it != _list.begin())
    {
        it--;
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

#ifndef SORTABLE_H
#define SORTABLE_H

#include "Updatable.h"

class Sortable : public Updatable
{
    friend class Sorter;

    public:
        Sortable() = default;
        virtual ~Sortable()
        {
            if(_holder != nullptr)
                *_holder = nullptr;
        }
        
    protected:
        int _priority = 0;
        int _id = 0;
        
    private:
        Sortable** _holder = nullptr;
};

#endif

#ifndef UPDATABLE_H
#define UPDATABLE_H

class Updatable
{
    friend class Updater;

    public:
        Updatable() = default;
        virtual ~Updatable()
        {
            if(_holder != nullptr)
                *_holder = nullptr;
        }

        virtual void update() = 0;
        bool active = false;
        
    private:
        Updatable** _holder = nullptr;
};

#endif

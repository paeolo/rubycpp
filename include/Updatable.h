#ifndef UPDATABLE_H
#define UPDATABLE_H

class Updatable
{
    friend class SpriteSorter;
    friend class Updater;

    public:
        Updatable() = default;
        virtual ~Updatable()
        {
            if(_holder != nullptr)
                *_holder = nullptr;
        }

        virtual void update() = 0;
        virtual void activate() { _active = true; }
        virtual void deactivate() { _active = true; }
        
    private:
        bool _active = false;
        Updatable** _holder = nullptr;
};

#endif

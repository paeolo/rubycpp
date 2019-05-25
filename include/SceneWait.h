#ifndef SCENE_WAIT_H
#define SCENE_WAIT_H

#include "Scene.h"

typedef void (*Task)(void);

class SceneWait : public Scene
{
    public:
        SceneWait(const unsigned int counter);
        SceneWait(const unsigned int counter, Task task);
        void init();
    private:
        void routine();
        const unsigned int _counter;
        Task _task = nullptr;
        bool _done = true;
};

#endif
#include "Engine.h"
#include "Scene.h"
#include "SceneWait.h"

SceneWait::SceneWait(const unsigned int counter): Scene(), _counter(counter) {}
SceneWait::SceneWait(const unsigned int counter, Task task): Scene(), _counter(counter)
{
    this->_task = task;
    this->_done = false;
}

void SceneWait::init()
{
    Scene::init();
    Engine::setCounter(_counter);
}

void SceneWait::routine()
{
    if(!this->_done)
    {
        this->_task();
        this->_done = true;
    }
    if(Engine::counter() == 0)
        this->_end = true;
}
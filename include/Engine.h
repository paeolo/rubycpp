#ifndef ENGINE_H
#define ENGINE_H

#include "Scene.h"
#include <queue>

class Engine
{
  public:
    static void initInterrupt();
    static void initOAM();
    static Scene* scene;
    void pushScene(Scene* scene);
    void popScene();
    static unsigned int counter();
    static void setCounter(unsigned int counter);

  private:
    static void VBlankInterrupt();
    std::queue<Scene*> _queue;
  
};

extern Engine engine;

#endif
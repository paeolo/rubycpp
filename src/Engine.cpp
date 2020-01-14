#include "Engine.h"
#include "Palette.h"
#include "Scene.h"
#include "Sprite.h"

#include <gba_interrupt.h>

IWRAM_DATA Scene* Engine::scene;
IWRAM_DATA Updater Engine::updater;
IWRAM_DATA unsigned int VBlankCounter = 0;

void Engine::pushScene(Scene* scene)
{
    _queue.push(scene);
}

void Engine::popScene()
{
    if(Engine::scene)
    {
        delete Engine::scene;
        Engine::scene = nullptr;
    }
    if(!this->_queue.empty())
    {
        Scene* scene = _queue.front();
        scene->init();
        Engine::scene = scene;
        this->_queue.pop();
    }
}

unsigned int Engine::counter()
{
    return VBlankCounter;
}

void Engine::setCounter(unsigned int counter)
{
    VBlankCounter = counter;
}

void Engine::initInterrupt()
{
    irqInit();
    irqSet(IRQ_VBLANK, Engine::VBlankInterrupt);
    irqEnable(IRQ_VBLANK);
}

void Engine::initOAM()
{
    for (int i = 0; i < 128; i++)
        Sprite::buffer.Object[i] = Sprite::emptyEntry;
}

void Engine::VBlankInterrupt()
{
    if(Engine::scene)
    {
        Palette::Flush();
        Sprite::Flush();

    }
    if(VBlankCounter > 0)
        --VBlankCounter;
}

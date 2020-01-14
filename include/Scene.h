#ifndef SCENE_H
#define SCENE_H

#include "Parser.h"

class Scene
{
    public:
        Scene() = default;
        Scene(const char* sceneName);
        virtual ~Scene() = default;
        
        virtual void init();
        void update();
        void activate();
        void deactivate();

    protected:
        virtual void routine() = 0;
        const char* _sceneName = nullptr;
        bool _active = false;
        bool _end = false;

        void init_Palette(Parser &p);
        void init_Tile(Parser &p);
        void init_Background(Parser &p);
        void init_Group(Parser &p);
        void init_Sprite(Parser &p);
};

#endif
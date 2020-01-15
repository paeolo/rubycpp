#ifndef SCENE_H
#define SCENE_H

#include "Parser.h"
#include "Updatable.h"

class Scene : public Updatable
{
    public:
        Scene() = default;
        Scene(const char* sceneName);
        virtual ~Scene() = default;
        
        virtual void init();
        void update();

    protected:
        virtual void routine() = 0;
        const char* _sceneName = nullptr;
        bool _end = false;

        void init_Palette(Parser &p);
        void init_Tile(Parser &p);
        void init_Background(Parser &p);
        void init_Group(Parser &p);
        void init_Sprite(Parser &p);
};

#endif

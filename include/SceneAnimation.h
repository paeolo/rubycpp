#ifndef SCENE_ANIMATION_H
#define SCENE_ANIMATION_H

#include "Animation.h"
#include "Scene.h"

#include <list>

typedef struct timeline_t
{
    int time;
    Animation* animation;
} timeline_t;

class SceneAnimation: public Scene
{
    public:
        SceneAnimation() = default;
        SceneAnimation(const char* sceneName);
        void init();
        void insert(int time, Animation* animation);

    private:
        void routine();
        void activate(Animation* animation);
        void init_Animation(Parser &p, Animation* &previous);
        
        std::list<timeline_t> _timeline;
        std::list<Animation*> _activeAnim;
        int _frame = 0;
};

#endif
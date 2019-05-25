#ifndef SCENE_FADE_H
#define SCENE_FADE_H

#include "Palette.h"
#include "Scene.h"

enum FadeType
{
    NORMAL = -2,
    REVERSE = 2
};

class SceneFade : public Scene
{
    public:
        SceneFade() = default;
        SceneFade(const char* sceneName, Color color, int fadeType);
        void init();

    private:
        void routine();
        Color _color = BLACK;
        int _fader = 0;
        int _fadeType = NORMAL;
};

#endif
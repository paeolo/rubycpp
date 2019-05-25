#include "Palette.h"
#include "Scene.h"
#include "SceneFade.h"

SceneFade::SceneFade(const char* sceneName, Color color, int fadeType): Scene(sceneName)
{
    this->_color = color;
    this->_fadeType = fadeType;
    this->_fader = (this->_fadeType > 0) ? 0 : 32;
}

void SceneFade::init()
{
    Scene::init();
    this->_fader += this->_fadeType;
}

void SceneFade::routine()
{
    int i;
    for (i= 0; i < 0x200; ++i)
        Palette::buffer[i] = Color::centroid(Palette::data[i], this->_color, this->_fader);
        
    if(this->_fader == 0 || this->_fader == 32)
        this->_end = true;
    else
        this->_fader += this->_fadeType;
}
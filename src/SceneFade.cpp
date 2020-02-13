#include "Allocator.h"
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

void SceneFade::parseNode(Parser &p)
{
    switch (p.node())
    {
        case ParserNode::NODE_PALETTE:
            this->init_Palette(p);
            break;
        default:
            Scene::parseNode(p);
            break;
    }
}

void SceneFade::init_Palette(Parser &p)
{
    if (p.exists(PAL_TAG))
    {
        int paletteNum = Allocator::Palette::allocate();
        Allocator::Palette::setByTag(p.value(PAL_TAG), paletteNum);
        Palette::LoadToData(p.string(PAL_FILE), 16 + paletteNum);
    }
    else
    {
        if (p.value(PAL_FILL))
            Palette::FillData(Color::Integer(p.value(PAL_COLOR)));
        else if (p.value(PAL_COPY))
            Palette::Copy(p.value(PAL_POSITION), p.value(PAL_DEST), p.value(PAL_OFFSET));
        else
            Palette::LoadToData(p.string(PAL_FILE), p.value(PAL_POSITION));
    }
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

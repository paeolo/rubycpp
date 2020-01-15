#include "Allocator.h"
#include "Animation.h"
#include "File.h"
#include "Parser.h"
#include "Scene.h"
#include "SceneAnimation.h"
#include "Sprite.h"

SceneAnimation::SceneAnimation(const char* sceneName): Scene(sceneName) {}

void SceneAnimation::init()
{
    this->_active = true;
    if(this->_sceneName)
    {
        File file(this->_sceneName, FileType::JSON);
        if(!file.exists())
            return;

        Parser p(&file);
        Animation* previous = nullptr;

        while(p.nextNode())
        {
            switch (p.node())
            {
                case ParserNode::NODE_PALETTE:
                    Scene::init_Palette(p);
                    break;
                case ParserNode::NODE_GROUP:
                    Scene::init_Group(p);
                    break;
                case ParserNode::NODE_SPRITE:
                    Scene::init_Sprite(p);
                    break;
                case ParserNode::NODE_ANIMATION:
                    this->init_Animation(p, previous);
                    break;
            }
        }
    }
}

void SceneAnimation::routine()
{
    while(!_timeline.empty() && _frame == _timeline.front().time)
    {
        Animation* animation = _timeline.front().animation;
        if(animation->previous)
            animation->previous->preempt();
        _timeline.pop_front();
        this->activate(animation);
    }

    std::list<Animation*>::iterator it = _activeAnim.begin();
    for(; it != _activeAnim.end(); ++it)
    {        
        if((*it)->end())
        {
            Animation* animation = (*it)->next;
            delete *it;
            it = _activeAnim.erase(it);
            if(animation)
                this->activate(animation);
        }
        else
            (*it)->routine();
    }
    
    if(_timeline.empty() && _activeAnim.empty())
        this->_end = true;
    else
        ++this->_frame;   
}

void SceneAnimation::activate(Animation* animation)
{
    animation->init();
    if(animation->next && animation->delay > 0)
    {
        this->insert(_frame + animation->delay, animation->next);
        animation->next = nullptr;
    }
    _activeAnim.push_back(animation);
}

void SceneAnimation::insert(int time, Animation* animation)
{
    if(_timeline.empty())
        _timeline.push_front({time, animation});
    else
    {
        std::list<timeline_t>::iterator it;
        for(it = _timeline.begin(); it != _timeline.end(); ++it)
        {
            if(time < it->time)
            {
                _timeline.insert(it, {time, animation});
                break;
            }
        }
        if(it == _timeline.end())
            _timeline.push_back({time, animation});
    }
}

void SceneAnimation::init_Animation(Parser &p, Animation* &previous)
{
    Animation* animation;
    if(p.exists(ANIM_GROUP))
    {
        animation = new Animation(
            p.value(ANIM_GROUP),
            ObjectType::OBJECT_SPRITE_GROUP,
            p.value(ANIM_ANIM)
        );
    }
    else
    {
        animation = new Animation(
            p.value(ANIM_SPRITE),
            ObjectType::OBJECT_SPRITE,
            p.value(ANIM_ANIM)
        );  
    }

    if(p.exists(ANIM_PARAMETER))
        animation->parameter = p.value(ANIM_PARAMETER);

    if(p.value(ANIM_PREMPT))
        animation->previous = previous;

    if(p.value(ANIM_NEXT) || p.value(ANIM_DELAY) > 0)
    {
        previous->next = animation;
        previous->delay = p.value(ANIM_DELAY);
    }
    else if(p.exists(ANIM_BEGIN))
        this->insert(p.value(ANIM_BEGIN), animation);

    previous = animation;
}

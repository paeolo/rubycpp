#include "Allocator.h"
#include "Background.h"
#include "Engine.h"
#include "File.h"
#include "Palette.h"
#include "Parser.h"
#include "register.h"
#include "Scene.h"
#include "Sprite.h"

Scene::Scene(const char* sceneName) : Scene()
{
    _sceneName = sceneName;
}

void Scene::activate() {this->_active = true;}
void Scene::deactivate() {this->_active = false;}

void Scene::update()
{
    if(this->_end)
        engine.popScene();  
    else if(this->_active)
        this->routine();
}

void Scene::init()
{
    this->_active = true;
    if(this->_sceneName)
    {
        LCD.DISPCNT = DISPCNT::MODE_0 | DISPCNT::OBJ_1D_MAP | DISPCNT::OBJ_ON;

        File file(this->_sceneName, FileType::JSON);
        if(!file.exists())
            return;

        Parser p(&file);
        while(p.nextNode())
        {
            switch (p.node())
            {
                case ParserNode::NODE_PALETTE:
                    this->init_Palette(p);
                    break;
                case ParserNode::NODE_TILE:
                    this->init_Tile(p);
                    break;
                case ParserNode::NODE_BACKGROUND:
                    this->init_Background(p);
                    break;
                case ParserNode::NODE_SPRITE:
                    this->init_Sprite(p);
                    break;
            }
        }
    }
}

void Scene::init_Palette(Parser &p)
{
    if(p.value(PAL_FILL))
        Palette::FillData(Color::Integer(p.value(PAL_COLOR)));
    else if(p.value(PAL_COPY))
        Palette::Copy(p.value(PAL_POSITION), p.value(PAL_DEST), p.value(PAL_OFFSET));
    else if(p.exists(PAL_TAG))
        allocator.createPalette(p.string(PAL_FILE), p.value(PAL_TAG));
    else
        Palette::Load(p.string(PAL_FILE), p.value(PAL_POSITION));
}

void Scene::init_Tile(Parser &p)
{
    if(p.exists(TILE_TAG))
        allocator.createTile(p.string(TILE_FILE), p.value(TILE_TAG));
    else
        Background::LoadTile4(p.string(TILE_FILE), p.value(TILE_CHAR), 0);
}

void Scene::init_Background(Parser &p)
{
    if(p.exists(BG_FILE))
        Background::LoadTileMap(p.string(BG_FILE), p.value(BG_MAP), 0);
    BGXCNT[p.value(BG_POSITION)] =
    (
        p.value(BG_PRIORITY)   |
        p.value(BG_CHAR) << 2  |
        p.value(BG_COLOR) << 7 |
        p.value(BG_MAP) << 8 |
        p.value(BG_SIZE) << 14
    );
    BGOFS[p.value(BG_POSITION)].x = p.value(BG_X);
    BGOFS[p.value(BG_POSITION)].y = p.value(BG_Y);
    LCD.DISPCNT |= 1 << (8 + p.value(BG_POSITION));
}

void Scene::init_Sprite(Parser &p)
{

    Sprite* sprite = allocator.createSprite
    (
        p.value(SPRITE_TAG),
        p.value(SPRITE_PALETTE_),
        p.value(SPRITE_TILE)
    );

    int affineMode = 0;
    if (p.value(SPRITE_AFFINE))
        affineMode += 1;
    if (p.value(SPRITE_DOUBLE))
        affineMode += 2;
    sprite->setShape
    (
        p.value(SPRITE_SHAPE),
        p.value(SPRITE_SIZE),
        affineMode
    );
    
    sprite->pos1.x = p.value(SPRITE_X);
    sprite->pos1.y = p.value(SPRITE_Y);
    sprite->tileOffset = p.value(SPRITE_TILEOFFSET);

    if(p.exists(SPRITE_PARENT))
        allocator.getSprite(p.value(SPRITE_PARENT))->addChild(sprite);
}
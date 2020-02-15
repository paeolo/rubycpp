#ifndef PARSER_KEY_H
#define PARSER_KEY_H

#define MAX_KEY 16

enum ParserNode
{
    NODE_PALETTE,
    NODE_TILE,
    NODE_BACKGROUND,
    NODE_GROUP,
    NODE_SPRITE,
    NODE_ANIMATION
};

enum PaletteKey
{
    PAL_COLOR,
    PAL_COPY,
    PAL_DEST,
    PAL_OFFSET,
    PAL_FILE,
    PAL_FILL,
    PAL_POSITION,
    PAL_TAG
};

enum TileKey
{
    TILE_CHAR,
    TILE_FILE,
    TILE_TAG,
    TILE_8BPP
};

enum BackgroundKey
{
    BG_CHAR,
    BG_COLOR,
    BG_FILE,
    BG_MAP,
    BG_POSITION,
    BG_PRIORITY,
    BG_SIZE,
    BG_X,
    BG_Y,
    BG_RESET,
    BG_HIDDEN
};

enum GroupKey
{
    GROUP_TAG,
    GROUP_X,
    GROUP_Y
};

enum SpriteKey
{
    SPRITE_AFFINE,
    SPRITE_DOUBLE,
    SPRITE_PALETTE_,
    SPRITE_SHAPE,
    SPRITE_SIZE,
    SPRITE_TAG,
    SPRITE_GROUP,
    SPRITE_TILE,
    SPRITE_TILEOFFSET,
    SPRITE_X,
    SPRITE_Y,
    SPRITE_PRIORITY
};

enum AnimationKey
{
    ANIM_ANIM,
    ANIM_BEGIN,
    ANIM_DELAY,
    ANIM_NEXT,
    ANIM_PREMPT,
    ANIM_END_SCENE,
    ANIM_SPRITE,
    ANIM_GROUP,
    ANIM_PARAMETER
};

#endif
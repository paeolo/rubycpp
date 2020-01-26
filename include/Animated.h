#ifndef ANIMATED_H
#define ANIMATED_H

#include <gba_types.h>

#define CMD_FRAME(_tileOffset, _duration) \
    {.frame = {.tileOffset = _tileOffset, .duration = _duration}}
#define CMD_LOOP(_count) \
    {.loop = {.type = -3, .count = _count}}
#define CMD_JUMP(_target) \
    {.jump = {.type = -2, .target = _target}}
#define CMD_END \
    {.type = -1}

enum CMDType
{
    FRAME = 0,
    END = -1,
    JUMP = -2,
    LOOP = -3
};

typedef struct CMDFrame
{
    unsigned int tileOffset:16;
    unsigned int duration:6;
    unsigned int hFlip:1;
    unsigned int vFlip:1;
} CMDFrame;

typedef struct CMDLoop
{
    int type:16;
    unsigned int count:6;
} CMDLoop;

typedef struct CMDJump
{
    int type:16;
    unsigned int target:6;
} CMDJump;

union CMDAnim
{
    int type: 16;
    CMDFrame frame;
    CMDLoop loop;
    CMDJump jump;
};

class Animated
{
    public:
        void start(const CMDAnim cmdAnim[]);
        void stop();
        int tileOffset = 0;
    protected:
        void routine();
    private:
        const CMDAnim *_cmdAnim = nullptr;
        int _index = 0;
        int _count = 0;
};

#endif

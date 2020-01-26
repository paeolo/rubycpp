#include "Animated.h"

void Animated::routine()
{
    if (_cmdAnim != nullptr)
    {
        switch (_cmdAnim[_index].type)
        {
        case CMDType::END:
            this->stop();
            break;
        case CMDType::JUMP:
            _index = _cmdAnim[_index].jump.target;
            break;
        case CMDType::LOOP:
            break;
        default:
            if (_count > 0)
                --_count;
            else
            {
                _count = _cmdAnim[_index].frame.duration;
                tileOffset = _cmdAnim[_index].frame.tileOffset;
            }
            if (_count == 0)
                ++_index;
            break;
        }
    }
}

void Animated::start(const CMDAnim cmdAnim[])
{
    _cmdAnim = cmdAnim;
    _index = 0;
    _count = 0;
}

void Animated::stop()
{
    _cmdAnim = nullptr;
}

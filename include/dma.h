#ifndef DMA_H
#define DMA_H

#include <gba_types.h>
#include "register.h"

namespace dma
{
    static inline void Set(const int channel , int src, int dst, int size, const int mode)
    {
        DMA[channel].DMASAD = src;
        DMA[channel].DMADAD = dst;
        DMA[channel].DMACNT_L = (u16) size;
        DMA[channel].DMACNT_H = (u16) (DMACNT::ENABLE | mode);
    }
    
    inline void Copy16(const int channel , const void *src, volatile void *dst, int size)
    {
        Set(channel, (int) src, (int) dst, size >> 1, BIT_16);
    }
    
    inline void Copy32(const int channel , const void *src, volatile void *dst, int size)
    {
        Set(channel, (int) src, (int) dst, size >> 2, BIT_32);
    }
    
    inline void Fill16(const int channel , int value, volatile void *dst, int size)
    {
        vu16 _value = (vu16) value;
        Set(channel, (int) &_value, (int) dst, size >> 1, SRC_FIXED | BIT_16);
    }

    inline void Fill32(const int channel , int value, volatile void *dst, int size)
    {
        vu32 _value = (vu32) value;
        Set(channel, (int) &_value, (int) dst, size >> 2, SRC_FIXED | BIT_32);
    }
}

#endif
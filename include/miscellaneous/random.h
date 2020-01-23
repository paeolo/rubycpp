#ifndef RANDOM_H
#define RANDOM_H
#ifdef __cplusplus
extern "C" {
#endif

#include <gba_types.h>

extern u32 gRngValue;
u16 Random(void);
#define Random32() (Random() | (Random() << 16))
void SeedRng(u16 seed);

#endif
#ifdef __cplusplus
}
#endif

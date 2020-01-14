#include "mgba.h"

#include <gba_types.h>
#include <stdio.h>
#include <stdarg.h>

#define DEBUG_ENABLE (*(volatile u16 *)(0x04FFF780))
#define DEBUG_FLAGS (*(volatile u16 *)(0x04FFF700))
#define DEBUG_STRING ((char *) (0x04FFF600))

void mgba_print(const char* s)
{
	int i = 0;
	DEBUG_ENABLE = (u16) 0xC0DE;

	while(*s)
	{
		DEBUG_STRING[i] = *s;
		s++;
		i++;
	}
	DEBUG_FLAGS = (u16) (MGBA_LOG_INFO | 0x0100);
    DEBUG_ENABLE = (u16) 0x0000;
}
void mgba_printf(const char* s, ...)
{
    char buffer[0x100];
    va_list args;
    va_start(args, s);
    vsprintf(buffer, s, args);
    va_end(args);
    mgba_print(buffer);
}
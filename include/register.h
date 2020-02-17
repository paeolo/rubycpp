#ifndef REGISTER_H
#define REGISTER_H
#ifdef __cplusplus
extern "C" {
#endif

#include <gba_types.h>
#include <gba_video.h>

#define LCD (*(volatile struct REG_LCD *) 0x4000000)
#define DMA ((volatile struct REG_DMA *) 0x40000B0)
#define SYS (*(volatile struct REG_SYS *) 0x4000200)
#define BGXCNT ((volatile u16 *) 0x4000008)
#define BGOFS ((volatile struct REG_BGOFS*) 0x4000010)
#define BGAFF ((volatile struct REG_BGAFF*) 0x4000020)

/* LCD */

struct REG_LCD
{
    u16  DISPCNT;   // LCD Control
    u16  REG_0;
    u16  DISPSTAT;  // General LCD Status
    u16  VCOUNT;    // Vertical Counter (LY)
    u16  BG0CNT;    // BG0 Control
    u16  BG1CNT;    // BG1 Control
    u16  BG2CNT;    // BG2 Control
    u16  BG3CNT;    // BG3 Control
    u16  BG0HOFS;   // BG0 X-Offset
    u16  BG0VOFS;   // BG0 Y-Offset
    u16  BG1HOFS;   // BG1 X-Offset
    u16  BG1VOFS;   // BG1 Y-Offset
    u16  BG2HOFS;   // BG2 X-Offset
    u16  BG2VOFS;   // BG2 Y-Offset
    u16  BG3HOFS;   // BG3 X-Offset
    u16  BG3VOFS;   // BG3 Y-Offset
    s16  BG2PA;     // BG2 Rotation/Scaling Parameter A (dx)
    s16  BG2PB;     // BG2 Rotation/Scaling Parameter B (dmx)
    s16  BG2PC;     // BG2 Rotation/Scaling Parameter C (dy)
    s16  BG2PD;     // BG2 Rotation/Scaling Parameter D (dmy)
    u32  BG2X;      // BG2 Reference Point X-Coordinate
    u32  BG2Y;      // BG2 Reference Point Y-Coordinate
    s16  BG3PA;     // BG3 Rotation/Scaling Parameter A (dx)
    s16  BG3PB;     // BG3 Rotation/Scaling Parameter B (dmx)
    s16  BG3PC;     // BG3 Rotation/Scaling Parameter C (dy)
    s16  BG3PD;     // BG3 Rotation/Scaling Parameter D (dmy)
    u32  BG3X;      // BG3 Reference Point X-Coordinate
    u32  BG3Y;      // BG3 Reference Point Y-Coordinate
    u16  WIN0H;     // Window 0 Horizontal Dimensions
    u16  WIN1H;     // Window 1 Horizontal Dimensions
    u16  WIN0V;     // Window 0 Vertical Dimensions
    u16  WIN1V;     // Window 1 Vertical Dimensions
    u16  WININ;     // Inside of Window 0 and 1
    u16  WINOUT;    // Inside of OBJ Window & Outside of Windows
    u16  MOSAIC;    // Mosaic Size
    u16  REG_1;
    u16  BLDCNT;    // Color Special Effects Selection
    u16  BLDALPHA;  // Alpha Blending Coefficients
    u16  BLDY;      // Brightness (Fade-In/Out) Coefficient
    u16  REG_2;
};

typedef LCDC_BITS DISPCNT;

enum DISPSTAT
{
	VBLANK_FLAG   =	(1 << 0),
	HBLANK_FLAG   =	(1 << 1),
	VCOUNTER_FLAG =	(1 << 2),
	VBLANK_ON	  =	(1 << 3),
	HBLANK_ON	  =	(1 << 4),
	VCOUNTER_ON	  =	(1 << 5)
};

enum BGCNT
{
    MOSAIC	  =	(1 << 6),  // Enable background mosaic
	COLOR_16  =	(0 << 7),  // Background uses 16 color tiles
	COLOR_256 =	(1 << 7),  // Background uses 256 color tiles
	WRAP	  =	(1 << 13), // Background wraps when scrolling
	SIZE_0	  =	(0 << 14), // Map Size 256x256
	SIZE_1	  =	(1 << 14), // Map Size 512x256
	SIZE_2	  =	(2 << 14), // Map Size 256x512
	SIZE_3	  =	(3 << 14)  // Map Size 512x512
};

struct REG_BGOFS
{
    u16 x;
    u16 y;
};

struct REG_BGAFF
{
    s16 A;     // Rotation/Scaling Parameter A (dx)
    s16 B;     // Rotation/Scaling Parameter B (dmx)
    s16 C;     // Rotation/Scaling Parameter C (dy)
    s16 D;     // Rotation/Scaling Parameter D (dmy)
    u32 X;      // Reference Point X-Coordinate
    u32 Y;      // Reference Point Y-Coordinate
};

enum BLDCNT
{ 
    TP1_BG0  =  (1 << 0),     // BG0 1st Target Pixel (Background 0)
    TP1_BG1  =  (1 << 1),     // BG1 1st Target Pixel (Background 0)
    TP1_BG2  =  (1 << 2),     // BG2 1st Target Pixel (Background 0)
    TP1_BG3  =  (1 << 3),     // BG3 1st Target Pixel (Background 0)
    TP1_OBJ  =  (1 << 4),     // OBJ 1st Target Pixel (Top-most OBJ pixel)
    TGT1_BD  =  (1 << 5),    // BD 1st Target Pixel (Backdrop)
    TP1_ALL  =  0b111111,
    EFFECT_NONE  =  (0 << 6), // Special effects disabled
    EFFECT_BLEND =  (1 << 6), // Alpha Blending (1st+2nd Target mixed)
    EFFECT_LIGHTEN = (2 << 6),// Brightness Increase (1st Target becomes whiter)
    EFFECT_DARKEN  = (3 << 6), // Brightness Decrease (1st Target becomes blacker)
    TP2_BG0  =  (1 << 8),
    TP2_BG1  =  (1 << 9),
    TP2_BG2  =  (1 << 10),
    TP2_BG3  =  (1 << 11),
    TP2_OBJ  =  (1 << 12),
    TP2_BD   =  (1 << 13),
    TP2_ALL  =   0b111111 << 8 
};

/* DMA */

struct REG_DMA
{
    u32  DMASAD;    // DMA Source Address
    u32  DMADAD;    // DMA Destination Address
    u16  DMACNT_L;  // DMA Word Count
    u16  DMACNT_H;  // DMA Control
};

enum DMACNT
{
    DST_INC		 =  (0 << 5), // Dest Addr Control : Increment
    DST_DEC		 =  (1 << 5), // Dest Addr Control : Decrement
    DST_FIXED	 =  (2 << 5), // Dest Addr Control : Fixed
    DST_RELOAD	 =  (3 << 5), // Dest Addr Control : Increment/Reload
    SRC_INC		 =  (0 << 7), // Source Addr Control : Increment
    SRC_DEC		 =  (1 << 7), // Source Addr Control : Decrement
    SRC_FIXED	 =  (2 << 7), // Source Addr Control : Fixed
    REPEAT		 =  (1 << 9), // DMA Repeat
    BIT_16       =  (0 << 10), // DMA Mode 16bit
    BIT_32		 =  (1 << 10), // DMA Mode 32bit
    GAME_PAK_DRQ =  (1 << 11), // Game Pak DRQ  - DMA3 only -
    IMMEDIATE	 =  (0 << 12), // DMA Start Timing : Immediate
    VBLANK		 =  (1 << 12), // DMA Start Timing : VBlank
    HBLANK		 =  (2 << 12), // DMA Start Timing : HBlank
    SPECIAL		 =  (3 << 12), // DMA Start Timing : Special
    IRQ			 =  (1 << 14), // IRQ upon end of Word Count 
    ENABLE		 =  (1 << 15)  // DMA Enable
};

/* SYSTEM CONTROL */

struct REG_SYS
{
    u16  IE;        // Interrupt Enable Register
    u16  IF;        // Interrupt Request Flags / IRQ Acknowledge
    u16  WAITCNT;   // Game Pak Waitstate Control
    u16  REG_0;
    u16  IME;       // Interrupt Master Enable Register
};

enum WAITCNT
{
    WS0_N_3 = (1 << 2),
    WS0_S_1 = (1 << 4),
    PREFETCH_ENABLE = (1 << 14)
};

#ifdef __cplusplus
}
#endif
#endif
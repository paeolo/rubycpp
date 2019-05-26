#ifndef SPRITE_H
#define SPRITE_H

#include "Background.h"
#include "AffineObject.h"
#include "Fixed.h"

#include <gba_types.h>
#include <gba_base.h>

/* VRAM */

#define OBJ_VRAM ((volatile Tile4 *) 0x6010000)
#define OBJ_SIZE 0x8000

/* OAM */

enum AffineMode
{
	AFFINE_DISABLE,
	AFFINE_ENABLE,
	AFFINE_HIDDEN,
	AFFINE_DOUBLE
};

enum SpriteShape
{
	SQUARE,
	HORIZONTAL,
	VERTICAL
};

enum SpriteSize
{
	SIZE_8,
	SIZE_16,
	SIZE_32,
	SIZE_64
};

typedef struct alignas(1)
{
	unsigned int y:8;
	unsigned int affineMode:2;
	unsigned int ObjMode:2;
	unsigned int mosaicMode:1;
	unsigned int colorMode:1;
  	unsigned int shape:2;
	unsigned int x:9;
	unsigned int matrixNum:5;
	unsigned int size:2;
	unsigned int tileNum:10;
	unsigned int priority:2;
	unsigned int paletteNum:4;
	Fixed coefficient;
} ObjectEntry;

typedef struct alignas(1)
{
	u16 OBJ_0[3];
	Fixed A;
	u16 OBJ_1[3];
	Fixed B;
	u16 OBJ_2[3];
	Fixed C;
	u16 OBJ_3[3];
	Fixed D;
} MatrixEntry;

typedef struct alignas(1)
{
	Fixed A;
	Fixed B;
	Fixed C;
	Fixed D;
} Matrix;

typedef union OAM_t
{
  ObjectEntry Object[128];
  MatrixEntry Matrix[32];
} OAM_t;

#define OAM_RAM (*(volatile OAM_t *) 0x7000000)
#define OAM_SIZE 0x400

class Sprite : public AffineObject
{
  public:
		Sprite() = default;
		~Sprite();
		Sprite(int tag, int paletteNum, int tileNum);

		ObjectEntry entry = ObjectEntry();
		int priority = 0;
		int tileOffset = 0;

		void update();
		void destroy();
		void scale(Fixed a, Fixed b);
		void rotate(Fixed a, Fixed b, int theta);
		void setShape(int shape, int size, int mode);
		void setId(int id);

		static int LoadTile4(const char* tileName, int tileNumber);
		static void Flush();
		EWRAM_DATA static OAM_t buffer;

	private:
		int _id = 0;
		int _tag = 0;
		int _tile = 0;
		pos_t _center = pos_t();
};

#endif
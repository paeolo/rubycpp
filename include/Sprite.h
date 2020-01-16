#ifndef SPRITE_H
#define SPRITE_H

#include <gba_types.h>
#include <gba_base.h>

#include "Affine.h"
#include "Background.h"
#include "Fixed.h"
#include "Sortable.h"
#include "SpriteSorter.h"
#include "Updatable.h"

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

typedef struct alignas(1) ObjectEntry
{
	unsigned int y:8;
	unsigned int affineMode:2;
	unsigned int ObjMode:2;
	unsigned int mosaicMode:1;
	unsigned int colorMode:1;
  	unsigned int shape:2;
	unsigned int x:9;
	unsigned int matrix:5;
	unsigned int size:2;
	unsigned int tileNum:10;
	unsigned int priority:2;
	unsigned int paletteNum:4;
	Fixed coefficient;

	static ObjectEntry makeEmptyEntry(void);

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

class Sprite final : public Affine, public Sortable
{
	public:
		void * operator new(std::size_t size);
		void operator delete(void* ptr);
		Sprite() = default;
		~Sprite();
		Sprite(int paletteNum, int tileNum, int tag = -1, int priority = 0, bool insert_updater = true);
		
		ObjectEntry entry = ObjectEntry();
		int tileOffset = 0;

		void update();
		void update(pos_t offset);
		void scale(Fixed a, Fixed b);
		void rotate(Fixed a, Fixed b, int theta);
		void setShape(SpriteShape shape, SpriteSize size, AffineMode mode);

		static int LoadTile4(const char* tileName, int tileNumber);
		static void Flush();
		IWRAM_DATA static const ObjectEntry emptyEntry;
		EWRAM_DATA static OAM_t buffer;
		IWRAM_DATA static SpriteSorter sorter;

	private:
		int _tag = -1;
		int _tile = 0;
		int _matrix = -1;
		pos_t _center = pos_t();
};

#endif

#include "tile.h"

const unsigned short tile::getConditionnum()
{
	return conditonnum;
}

unsigned short tile::getBottomnum()
{
	return bottomnum;
}

short tile::getBR(unsigned short number)
{
	return position[ROW] + bottom[number][ROW];
}

short tile::getBC(unsigned short number)
{
	return position[COLUMN] + bottom[number][COLUMN];
}

short tile::getSR(unsigned short number)
{
	return shape[number][ROW];
}

short tile::getSC(unsigned short number)
{
	return shape[number][COLUMN];
}

short tile::getR(unsigned short number)
{
	return position[ROW] + shape[number][ROW];
}

short tile::getC(unsigned short number)
{
	return position[COLUMN] + shape[number][COLUMN];
}

void tile::move(char direction)
{
	switch (direction)
	{
	case 'a':--position[COLUMN]; break;
	case 'd':++position[COLUMN]; break;
	case 's':++position[ROW]; break;
	case 'w':--position[ROW]; break;
	default:return;
	}
}

tiletype tile::getType()
{
	return type;
}

tile::tile(const unsigned short conditionnum, tiletype type) :condition(0), conditonnum(conditionnum),type(type)
{
	shape[0][ROW] = shape[0][COLUMN] = 0;
	position[COLUMN] = 5;
}

//以下代码在编写时很不容易，稍微不注意就有可能出错，但一劳永逸，使用方便
tile_I::tile_I() :tile(2, I)
{
	bottomnum = 1;
	position[ROW] = 1;
	bottom[0][COLUMN] = shape[1][COLUMN] = shape[2][COLUMN] = shape[3][COLUMN] = 0;
	shape[1][ROW] = -1;
	shape[2][ROW] = 1;
	shape[3][ROW] = 2;
	bottom[0][ROW] = 3;
}

void tile_I::turnAround()
{
	switch ((++condition) % conditonnum)
	{
	case 0:
	{
		bottomnum = 1;
		bottom[0][COLUMN] = shape[1][COLUMN] = shape[2][COLUMN] = shape[3][COLUMN] = 0;
		shape[1][ROW] = -1;
		shape[2][ROW] = 1;
		shape[3][ROW] = 2;
		bottom[0][ROW] = 3;
	}break;
	case 1:
	{
		bottomnum = 4;
		bottom[0][COLUMN] = shape[1][COLUMN] = -1;
		bottom[1][COLUMN] = shape[1][ROW] = shape[2][ROW] = shape[3][ROW] = 0;
		bottom[0][ROW] = bottom[1][ROW] = bottom[2][ROW] = bottom[3][ROW] = bottom[2][COLUMN] = shape[2][COLUMN] = 1;
		bottom[3][COLUMN] = shape[3][COLUMN] = 2;
	}break;
	default:return;
	}
}

tile_J::tile_J() :tile(4, J)
{
	bottomnum = 2;
	++position[COLUMN];
	position[ROW] = 2;
	bottom[0][COLUMN] = shape[1][ROW] = shape[3][COLUMN] = -1;
	bottom[1][COLUMN] = shape[1][COLUMN] = shape[2][COLUMN] = 0;
	shape[2][ROW] = shape[3][ROW] = 1;
	bottom[0][ROW] = bottom[1][ROW] = 2;
}

void tile_J::turnAround()
{
	switch ((++condition) % conditonnum)
	{
	case 0:
	{
		bottomnum = 2;
		bottom[0][COLUMN] = shape[1][ROW] = shape[3][COLUMN] = -1;
		bottom[1][COLUMN] = shape[1][COLUMN] = shape[2][COLUMN] = 0;
		shape[2][ROW] = shape[3][ROW] = 1;
		bottom[0][ROW] = bottom[1][ROW] = 2;
	}break;
	case 1:
	{
		bottomnum = 3;
		bottom[0][COLUMN] = shape[1][COLUMN] = shape[2][COLUMN] = shape[1][ROW] = -1;
		bottom[1][COLUMN] = shape[2][ROW] = shape[3][ROW] = 0;
		bottom[0][ROW] = bottom[1][ROW] = bottom[2][ROW] = bottom[2][COLUMN] = shape[3][COLUMN] = 1;
	}break;
	case 2:
	{
		bottomnum = 2;
		shape[1][ROW] = shape[2][ROW] = -1;
		bottom[0][COLUMN] = bottom[1][ROW] = shape[2][COLUMN] = shape[3][COLUMN] = 0;
		bottom[1][COLUMN] = shape[1][COLUMN] = shape[3][ROW] = 1;
		bottom[0][ROW] = 2;
	}break;
	case 3:
	{
		bottomnum = 3;
		bottom[0][COLUMN] = shape[1][COLUMN] = -1;
		bottom[1][COLUMN] = shape[1][ROW] = shape[2][ROW] = 0;
		bottom[0][ROW] = bottom[1][ROW] = bottom[2][COLUMN] = shape[2][COLUMN] = shape[3][COLUMN] = shape[3][ROW] = 1;
		bottom[2][ROW] = 2;
	}break;
	default:return;
	}
}

tile_L::tile_L() : tile(4, L)
{
	bottomnum = 2;
	position[ROW] = 2;
	shape[1][ROW] = -1;
	bottom[0][COLUMN] = shape[1][COLUMN] = shape[2][COLUMN] = 0;
	bottom[1][COLUMN] = shape[2][ROW] = shape[3][ROW] = shape[3][COLUMN] = 1;
	bottom[0][ROW] = bottom[1][ROW] = 2;
}

void tile_L::turnAround()
{
	switch ((++condition) % conditonnum)
	{
	case 0:
	{
		bottomnum = 2;
		shape[1][ROW] = -1;
		bottom[0][COLUMN] = shape[1][COLUMN] = shape[2][COLUMN] = 0;
		bottom[1][COLUMN] = shape[2][ROW] = shape[3][ROW] = shape[3][COLUMN] = 1;
		bottom[0][ROW] = bottom[1][ROW] = 2;
	}break;
	case 1:
	{
		bottomnum = 3;
		bottom[0][COLUMN] = shape[1][COLUMN] = shape[2][COLUMN] = -1;
		bottom[1][COLUMN] = shape[2][ROW] = shape[3][ROW] = 0;
		bottom[1][ROW] = bottom[2][ROW] = bottom[2][COLUMN] =shape[1][ROW] = shape[3][COLUMN] = 1;
		bottom[0][ROW] = 2;
	}break;
	case 2:
	{
		bottomnum = 2;
		bottom[0][COLUMN] = shape[1][COLUMN] = shape[1][ROW] = shape[2][ROW] = -1;
		bottom[0][ROW] = bottom[1][COLUMN] = shape[2][COLUMN] = shape[3][COLUMN] = 0;
		shape[3][ROW] = 1;
		bottom[1][ROW] = 2;
	}break;
	case 3:
	{
		bottomnum = 3;
		bottom[0][COLUMN] = shape[1][COLUMN] = shape[3][ROW] = -1;
		bottom[1][COLUMN] = shape[1][ROW] = shape[2][ROW] = 0;
		bottom[0][ROW] = bottom[1][ROW] = bottom[2][ROW] = bottom[2][COLUMN] = shape[2][COLUMN] = shape[3][COLUMN] = 1;
	}break;
	default:return;
	}
}

tile_O::tile_O() : tile(0, O)
{
	bottomnum = 2;
	position[ROW] = 2;
	bottom[0][COLUMN] = shape[1][ROW] = shape[3][COLUMN] = 0;
	bottom[1][COLUMN] = shape[1][COLUMN] = shape[2][COLUMN] = shape[3][ROW] = shape[2][ROW] = 1;
	bottom[0][ROW] = bottom[1][ROW] = 2;
}

void tile_O::turnAround()
{
	return;
}

tile_S::tile_S() : tile(2, S)
{
	bottomnum = 3;
	position[ROW] = 3;
	bottom[0][COLUMN] = shape[1][COLUMN] = shape[2][ROW] = shape[3][ROW] = -1;
	bottom[1][COLUMN] = bottom[2][ROW] = shape[1][ROW] = shape[2][COLUMN] = 0;
	bottom[0][ROW] =bottom[1][ROW] = bottom[2][COLUMN] = shape[3][COLUMN] = 1;
}

void tile_S::turnAround()
{
	switch ((++condition) % conditonnum)
	{
	case 0:
	{
		bottomnum = 3;
		bottom[0][COLUMN] = shape[1][COLUMN] = shape[2][ROW] = shape[3][ROW] = -1;
		bottom[1][COLUMN] = bottom[2][ROW] = shape[1][ROW] = shape[2][COLUMN] = 0;
		bottom[0][ROW] = bottom[1][ROW] = bottom[2][COLUMN] = shape[3][COLUMN] = 1;
	}break;
	case 1:
	{
		bottomnum = 2;
		bottom[0][COLUMN] = shape[2][ROW] = shape[2][COLUMN] = -1;
		bottom[1][COLUMN] = shape[3][COLUMN] = 0;
		bottom[0][ROW] = shape[3][ROW] = 1;
		bottom[1][ROW] = 2;
	}break;
	default:return;
	}
}

tile_Z::tile_Z() :tile(2, Z)
{
	bottomnum = 3;
	position[ROW] = 3;
	bottom[0][COLUMN] = shape[1][ROW] = shape[1][COLUMN] = shape[2][ROW] = -1;
	bottom[0][ROW] = bottom[1][COLUMN] = shape[2][COLUMN] = shape[3][ROW] = 0;
	bottom[1][ROW] = bottom[2][ROW] = bottom[2][COLUMN] = shape[3][COLUMN] = 1;
}

void tile_Z::turnAround()
{
	switch ((++condition) % conditonnum)
	{
	case 0:
	{
		bottomnum = 3;
		bottom[0][COLUMN] = shape[1][ROW] = shape[1][COLUMN] = shape[2][ROW] = -1;
		bottom[0][ROW] = bottom[1][COLUMN] = shape[2][COLUMN] = shape[3][ROW] = 0;
		bottom[1][ROW] = bottom[2][ROW] = bottom[2][COLUMN] = shape[3][COLUMN] = 1;
	}break;
	case 1:
	{
		bottomnum = 2;
		shape[1][ROW] = -1;
		bottom[0][COLUMN] = shape[2][COLUMN] = 0;
		bottom[1][ROW] = bottom[1][COLUMN] = shape[1][COLUMN] = shape[2][ROW] = 1;
		bottom[0][ROW] = 2;
	}break;
	default:return;
	}
}

tile_T::tile_T() :tile(4, T)
{
	bottomnum = 3;
	position[ROW] = 2;
	bottom[0][COLUMN] = shape[1][COLUMN] = -1;
	bottom[1][COLUMN] = shape[1][ROW] = shape[3][ROW] = shape[2][COLUMN] = 0;
	bottom[0][ROW] = bottom[2][ROW] = bottom[2][COLUMN] = shape[2][ROW] = shape[3][COLUMN] = 1;
	bottom[1][ROW] = 2;
}

void tile_T::turnAround()
{
	switch ((++condition) % conditonnum)
	{
	case 0:
	{
		bottomnum = 3;
		bottom[0][COLUMN] = shape[1][COLUMN] = -1;
		bottom[1][COLUMN] = shape[1][ROW] = shape[3][ROW] = shape[2][COLUMN] = 0;
		bottom[0][ROW] = bottom[2][ROW] = bottom[2][COLUMN] = shape[2][ROW] = shape[3][COLUMN] = 1;
		bottom[1][ROW] = 2;
	}break;
	case 1:
	{
		bottomnum = 2;
		bottom[0][COLUMN] = shape[3][ROW] = -1;
		bottom[1][COLUMN] = shape[3][COLUMN] = 0;
		bottom[0][ROW] = 1;
		bottom[1][ROW] = 2;
	}break;
	case 2:
	{
		bottomnum = 3;
		bottom[0][COLUMN] = -1;
		bottom[1][COLUMN] = shape[2][ROW] = 0;
		bottom[0][ROW] = bottom[1][ROW] = bottom[2][ROW] = bottom[2][COLUMN] = shape[2][COLUMN] = 1;
	}break;
	case 3:
	{
		bottomnum = 2;
		bottom[0][COLUMN] = shape[1][COLUMN] = 0;
		bottom[1][ROW] = bottom[1][COLUMN] = shape[1][ROW] = 1;
		bottom[0][ROW] = 2;
	}break;
	default:return;
	}
}
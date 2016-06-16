#pragma once

#include "ChunkSource.h"

struct ChunkViewSource
: public ChunkSource
{
	struct ViewArea
	{
		char filler[48];
		int posX;
		int posY;
		int posZ;
	};

	ViewArea& getArea();
};

#pragma once

struct Level;
struct Dimension;
struct ChunkSource;
struct BlockPos;
#include "../../CommonTypes.h"

struct BlockSource
{
	char filler[80];

	BlockSource(Level&, Dimension&, ChunkSource&, bool, bool);

	bool isEmptyBlock(const BlockPos&);
	BlockID getBlockID(const BlockPos&);
	bool setBlock(const BlockPos&, BlockID, int);
	Level& getLevel() const;
};

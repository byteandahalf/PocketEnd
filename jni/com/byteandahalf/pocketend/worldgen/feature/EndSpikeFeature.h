#pragma once

#include "com/mojang/minecraftpe/world/gen/feature/Feature.h"

struct EndSpikeFeature
: public Feature
{
	int groundBlock;

	EndSpikeFeature(int);

	virtual bool place(BlockSource&, const BlockPos&, Random&);
};

#pragma once

#include "com/mojang/minecraftpe/world/biome/Biome.h"
#include "com/mojang/minecraftpe/world/biome/BiomeDecorator.h"

struct TheEndBiome
: public Biome
{
	TheEndBiome(int);

	virtual const Color getSkyColor(float);
	virtual void decorate(BlockSource*, Random&, LevelChunk&, const BlockPos&, float);

	struct Decorator
	:public BiomeDecorator
	{
		Feature* spikeFeature;

		Decorator();
		virtual ~Decorator();

		void decorate(BlockSource*, Random&, const BlockPos&);
	};
};

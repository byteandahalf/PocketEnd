#pragma once

#include "com/mojang/minecraftpe/util/Random.h"

#include "com/mojang/minecraftpe/world/gen/ChunkSource.h"

struct EndRandomLevelSource
: public ChunkSource
{
	Random endRNG;
	PerlinNoise* noiseGenerators[5];
	float densities[5000];

	EndRandomLevelSource(Level*, Dimension*, unsigned int);

	float* getHeights(float*, int, int, int, int, int, int);
	void prepareHeights(int, int, LevelChunk&);
	void buildSurfaces(LevelChunk&, ChunkPos);

	virtual ~EndRandomLevelSource();
	virtual LevelChunk* requestChunk(const ChunkPos& pos, ChunkSource::LoadMode);
	virtual void loadChunk(LevelChunk&);

	virtual void postProcess(ChunkViewSource&);

	//virtual std::vector<Mob*> getMobsAt(BlockSource&, EntityType, const BlockPos&);
};

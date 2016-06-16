#pragma once

struct PerlinNoise;

#include "ChunkSource.h"

struct HellRandomLevelSource
:public ChunkSource
{
	PerlinNoise* noiseGen1; // 24
	PerlinNoise* noiseGen2; // 28
	PerlinNoise* noiseGen3; // 32
	PerlinNoise* noiseGen4; // 36
	PerlinNoise* noiseGen5; // 40
	PerlinNoise* noiseGen6; // 44
	PerlinNoise* noiseGen7; // 48
	char filler[88]; // 52

	HellRandomLevelSource(Level*, Dimension*, unsigned int);

	virtual ~HellRandomLevelSource();
	virtual LevelChunk* requestChunk(const ChunkPos& pos, ChunkSource::LoadMode);
	virtual void loadChunk(LevelChunk&);
	virtual void postProcess(ChunkViewSource&);
	virtual std::vector<Mob*> getMobsAt(BlockSource&, EntityType, const BlockPos&);
};

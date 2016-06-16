#pragma once

#include "ChunkSource.h"

struct RandomLevelSource
: public ChunkSource
{
	char filler[384];

	RandomLevelSource(Level*, Dimension*, unsigned int, bool);

	virtual ~RandomLevelSource();
	virtual LevelChunk* requestChunk(const ChunkPos&, ChunkSource::LoadMode);
	virtual void loadChunk(LevelChunk&);
	virtual void postProcess(ChunkViewSource&);
	virtual void postProcessMobsAt(BlockSource*, int, int, Random&);
};

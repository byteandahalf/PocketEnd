#pragma once

#include "ChunkSource.h"

struct FlatLevelSource
: public ChunkSource {

	static const std::string DEFAULT_LAYERS;

	FlatLevelSource(Level*, Dimension*, const std::string&);

	virtual ~FlatLevelSource();
	virtual void loadChunk(LevelChunk&);
	virtual LevelChunk* requestChunk(const ChunkPos&, ChunkSource::LoadMode);
	virtual void postProcess(ChunkViewSource&);
};

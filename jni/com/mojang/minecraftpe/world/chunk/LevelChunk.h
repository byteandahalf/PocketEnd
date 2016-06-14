#pragma once

struct Level;
struct Dimension;
struct ChunkSource;
struct ChunkPos;
struct ChunkBlockPos;
struct Biome;

#include "ChunkState.h"

#include <cstdint>

struct LevelChunk
{
	char filler[0x151C8];

	LevelChunk(Level&, Dimension&, const ChunkPos&, bool);

	uint8_t* getRawBlocks();
	void recalcHeightmap();
	ChunkPos& getPosition() const;
	void setGenerator(ChunkSource*);
	void setUnsaved();
	void changeState(ChunkState, ChunkState);

	void setBiome(const Biome&, const ChunkBlockPos&);

	void* operator new(unsigned int);
};

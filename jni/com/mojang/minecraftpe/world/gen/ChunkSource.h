#pragma once

struct LevelChunk;
struct Level;
struct Dimension;
struct ChunkPos;
struct ChunkViewSource;
struct BlockSource;
struct BlockPos;
struct Random;
struct Mob;

#include "../entity/EntityType.h"

#include <memory>
#include <vector>
#include <functional>

struct ChunkSource
{
	int _chunkSide; // 4
	Level* level; // 8
	Dimension* dimension; // 12
	bool ownsParent; // 16
	int idk; // 20

	enum class LoadMode : int {
		NONE,
		DEFERRED,
		EMPTY
	};

	ChunkSource(Level*, Dimension*, int);

	Level& getLevel() const;
	Dimension& getDimension() const;

	virtual ~ChunkSource();
	virtual LevelChunk& getExistingChunk(const ChunkPos&);
	virtual LevelChunk* requestChunk(const ChunkPos& pos, ChunkSource::LoadMode);
	virtual bool releaseChunk(LevelChunk&);
	virtual void postProcess(ChunkViewSource&);
	virtual void loadChunk(LevelChunk&);
	virtual void postProcessMobsAt(BlockSource*, int, int, Random&);
	virtual std::vector<Mob*> getMobsAt(BlockSource&, EntityType, const BlockPos&);
	virtual bool saveLiveChunk(LevelChunk&);
	virtual void hintDiscardBatchBegin();
	virtual void hintDiscardBatchEnd();
	virtual void acquireDiscarded(std::unique_ptr<LevelChunk>&&);
	virtual void getStoredChunks() const;
	virtual void getStoredChunks();
	virtual bool compact();
	virtual void waitDiscardFinished();
	virtual ChunkViewSource& getView(const BlockPos&, const BlockPos&, ChunkSource::LoadMode, bool, const std::function<void(LevelChunk*&)>&);
};

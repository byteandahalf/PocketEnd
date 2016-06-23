#pragma once

struct CompoundTag;
struct Packet;
struct MoveEntityPacketData;
struct Level;
struct ChunkSource;

#include "DimensionId.h"
#include "GeneratorType.h"
#include "../../client/renderer/Color.h"

#include "../listeners/LevelListener.h"

struct Dimension
: public LevelListener
{
	char filler[84]; // 4
	Level& level; // 88
	char filler2[88]; // 92

	Dimension(Level&, DimensionId);

	Color getSkyColor(const Entity&, float);

	std::unique_ptr<ChunkSource> _createGenerator(GeneratorType);
	void setCeiling(bool);

	static std::unique_ptr<Dimension> createNew(DimensionId, Level&);

	virtual ~Dimension();
	virtual void onBlockChanged(BlockSource&, const BlockPos&, FullBlock, FullBlock, int);
	virtual void onBlockEvent(BlockSource&, int, int, int, int, int);
	virtual void onNewChunkFor(Player&, LevelChunk&);
	virtual void init();
	virtual void tick();
	virtual void updateLightRamp();
	virtual bool isNaturalDimension() const;
	virtual bool isValidSpawn(int, int) const;
	virtual Color getFogColor(float) const;
	virtual float getFogDistanceScale() const;
	virtual bool isFoggyAt(int, int) const;
	virtual float getCloudHeight() const;
	virtual bool mayRespawn() const;
	virtual bool hasGround() const;
	virtual int getSpawnYPosition();
	virtual bool hasBedrockFog();
	virtual float getClearColorScale();
	virtual const std::string getName() const = 0;
	virtual void load(const CompoundTag&);
	virtual void save(CompoundTag&);
	virtual void sendDimensionPackets();
	virtual void sendBroadcast(const Packet&, Player*);
	virtual void addMoveEntityPacket(const MoveEntityPacketData&);
	virtual void addSetEntityMotionPacket(Entity&);
	virtual float getTimeOfDay(int, float) const;
};

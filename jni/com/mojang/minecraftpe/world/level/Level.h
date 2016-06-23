#pragma once

struct Player;
struct LevelStorage;
struct LevelSettings;
struct SoundPlayer;
struct EntityDamageSource;
struct Difficulty;
struct LightLayer;
struct LevelChunk;

#include <string>

#include "../listeners/BlockSourceListener.h"

struct Level
: public BlockSourceListener
{
	Level(SoundPlayer&, std::unique_ptr<LevelStorage>, const std::string&, const LevelSettings&, bool);

	unsigned int getSeed();
	Player& getLocalPlayer() const;

	virtual ~Level();
	virtual void onSourceCreated(BlockSource&);
	virtual void onSourceDestroyed(BlockSource&);
	virtual void onBlockChanged(BlockSource&, const BlockPos&, FullBlock, FullBlock, int);
	virtual void addEntity(std::unique_ptr<Entity>);
	virtual void addPlayer(std::unique_ptr<Player>);
	virtual void addGlobalEntity(std::unique_ptr<Entity>);
	virtual void onPlayerDeath(Player&, const EntityDamageSource&);
	virtual void tick();
	virtual void directTickEntities(BlockSource&);
	virtual void updateSleepingPlayerList();
	virtual void setDifficulty(Difficulty);
	virtual void runLightUpdates(BlockSource&, const LightLayer&, const BlockPos&, const BlockPos&);
	virtual void onNewChunkFor(Player&, LevelChunk&);
	virtual void onChunkLoaded(LevelChunk&);
	virtual void removeEntity(std::unique_ptr<Entity>&&, bool);
	virtual void removeEntity(Entity&, bool);
	virtual void onAppSuspended();
};

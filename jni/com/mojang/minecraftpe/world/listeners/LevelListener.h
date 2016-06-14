#pragma once

struct ParticleType;
struct Vec3;
struct EntityLocation;
struct Player;
struct LevelChunk;
struct LevelEvent;
struct ImageData;

#include <string>

#include "BlockSourceListener.h"

struct LevelListener
: public BlockSourceListener
{
	virtual ~LevelListener();
	virtual void allChanged();
	virtual void addParticle(ParticleType, const Vec3&, const Vec3&, int);
	virtual void playSound(const Entity&, EntityLocation, const std::string&, float, float);
	virtual void playSound(const std::string&, const Vec3&, float, float);
	virtual void playMusic(const std::string&, const Vec3&, float);
	virtual void playStreamingMusic(const std::string&, int, int, int);
	virtual void onEntityAdded(Entity&);
	virtual void onEntityRemoved(Entity&);
	virtual void onNewChunkFor(Player&, LevelChunk&);
	virtual void levelEvent(LevelEvent, const Vec3&, int);
	virtual void takePicture(ImageData&, Entity*, Entity*, bool, const std::string&);
};

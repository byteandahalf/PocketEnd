#pragma once

struct BiomeDecorator;
struct Random;
struct Color;
struct Feature;
struct BlockPos;
struct BlockSource;
struct LevelChunk;
struct Mob;
#include "../entity/EntityType.h"
#include "MobSpawnerData.h"

#include <vector>
#include <memory>

struct Biome
{
	enum class BiomeType : int
	{
		Beach,
		Desert,
		ExtremeHills,
		Flat,
		Forest,
		Hell,
		Ice,
		Jungle,
		Mesa,
		MushroomIsland,
		Ocean,
		Plain,
		River,
		Savanna,
		StoneBeach,
		Swamp,
		Taiga,
		TheEnd
	};

	BiomeDecorator* decorator; // 4
	std::vector<MobSpawnerData> hostileMobs; // 8
	std::vector<MobSpawnerData> friendlyMobs; // 20
	std::vector<MobSpawnerData> waterMobs; // 32
	char filler[24]; // 44
	uint8_t surfaceBlock; // 68
	uint8_t fillerBlock; // 70
	char filler2[76]; // 72
	int biomeId; // 148
	int idk; // 152

	Biome(int, BiomeType, std::unique_ptr<BiomeDecorator>);

	Biome* setName(const std::string&);
	Biome* setNoRain();

	virtual void setColor(int);
	virtual void setColor(int, bool);
	virtual ~Biome();
	virtual Feature* getTreeFeature(Random*);
	virtual Feature* getGrassFeature(Random*);
	virtual float getTemperature();
	virtual float adjustScale(float);
	virtual float adjustDepth(float);
	virtual const Color getSkyColor(float);
	virtual std::vector<Mob*> getMobs(EntityType);
	virtual float getCreatureProbability();
	virtual int getFoliageColor();
	virtual void* getRandomFlowerTypeAndData(Random&, const BlockPos&);
	virtual void decorate(BlockSource*, Random&, LevelChunk&, const BlockPos&, float);
	virtual void buildSurfaceAt(Random&, LevelChunk&, const BlockPos&, float);
	virtual int getGrassColor(const BlockPos&);
	virtual void refreshBiome(unsigned int);
	virtual void getTemperatureCategory() const;
	virtual bool isSame(Biome*);
	virtual bool isHumid();
	virtual Biome* createMutatedCopy(int);

	static void initBiomes();
	static const Biome& getBiome(int);

	static std::vector<Mob*> EMPTY_MOBLIST;

	static Biome* hell;
	static Biome* sky;
};

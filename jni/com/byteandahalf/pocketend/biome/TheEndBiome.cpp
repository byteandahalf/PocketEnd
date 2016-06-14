#include "com/mojang/minecraftpe/client/renderer/Color.h"
#include "com/mojang/minecraftpe/util/Random.h"
#include "com/mojang/minecraftpe/world/level/BlockPos.h"

#include "../worldgen/feature/EndSpikeFeature.h"
#include "TheEndBiome.h"

TheEndBiome::TheEndBiome(int biomeId)
: Biome(biomeId, Biome::BiomeType::TheEnd, std::unique_ptr<BiomeDecorator>(new TheEndBiome::Decorator()))
{
	hostileMobs.clear();
	friendlyMobs.clear();
	waterMobs.clear();
	hostileMobs.push_back({10, 0xB26, 4, 10});
	
	surfaceBlock = 3;
	fillerBlock = 3;
}

const Color TheEndBiome::getSkyColor(float)
{
	return Color::BLACK;
}

void TheEndBiome::decorate(BlockSource* region, Random& rng, LevelChunk& chunk, const BlockPos& pos, float)
{
	((TheEndBiome::Decorator*) decorator)->decorate(region, rng, pos);
}

/*
*	TheEndBiome::Decorator
*/
TheEndBiome::Decorator::Decorator()
: BiomeDecorator()
{
	spikeFeature = new EndSpikeFeature(121);
}

TheEndBiome::Decorator::~Decorator()
{
	delete spikeFeature;
}

void TheEndBiome::Decorator::decorate(BlockSource* region, Random& rng, const BlockPos& pos)
{
	return;
	// This code crashes
	int i = pos.x + rng.nextInt(16) + 8;
	int j = pos.z + rng.nextInt(16) + 8;
	int k = 100;//currentWorld.getTopSolidOrLiquidBlock(i, j);
	spikeFeature->place(*region, {i, k, j}, rng);
}

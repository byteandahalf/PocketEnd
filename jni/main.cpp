#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <substrate.h>

#include <memory>

#include "com/mojang/minecraftpe/world/dimension/NormalDimension.h"
#include "com/mojang/minecraftpe/world/dimension/HellDimension.h"
#include "com/mojang/minecraftpe/world/gen/RandomLevelSource.h"
#include "com/mojang/minecraftpe/world/gen/FlatLevelSource.h"
#include "com/mojang/minecraftpe/world/gen/HellRandomLevelSource.h"
#include "com/mojang/minecraftpe/world/level/Level.h"

#include "com/byteandahalf/pocketend/dimension/EndDimension.h"
#include "com/byteandahalf/pocketend/worldgen/EndRandomLevelSource.h"
#include "com/byteandahalf/pocketend/biome/TheEndBiome.h"

static void (*_Biome$initBiomes)();
static void Biome$initBiomes()
{
	_Biome$initBiomes();

	Biome::sky = (new TheEndBiome(9))->setName("Sky")->setNoRain();
}

static std::unique_ptr<Dimension> (*_Dimension$createNew)(DimensionId, Level&);
static std::unique_ptr<Dimension> Dimension$createNew(DimensionId dimensionId, Level& level)
{
	switch(dimensionId)
	{
	case DimensionId::OVERWORLD:
		return std::unique_ptr<Dimension>(new NormalDimension(level));
	case DimensionId::HELL:
		return std::unique_ptr<Dimension>(new EndDimension(level));

	default:
		return std::unique_ptr<Dimension>{};
	}
}

static std::unique_ptr<ChunkSource> (*_Dimension$_createGenerator)(Dimension*, GeneratorType);
static std::unique_ptr<ChunkSource> Dimension$_createGenerator(Dimension* self, GeneratorType type)
{
	switch(type)
	{
	case GeneratorType::LIMIT:
		return std::unique_ptr<ChunkSource>(new RandomLevelSource(&self->level, self, self->level.getSeed(), true));
	case GeneratorType::INFINITE:
		return std::unique_ptr<ChunkSource>(new RandomLevelSource(&self->level, self, self->level.getSeed(), false));
	case GeneratorType::FLAT:
		return std::unique_ptr<ChunkSource>(new FlatLevelSource(&self->level, self, FlatLevelSource::DEFAULT_LAYERS));
	case GeneratorType::NETHER:
		return std::unique_ptr<ChunkSource>(new EndRandomLevelSource(&self->level, self, self->level.getSeed()));
	
	default:
		return std::unique_ptr<ChunkSource>{};
	}
}

static void setupHooks(void* handle)
{
	MSHookFunction((void*) &Biome::initBiomes, (void*) &Biome$initBiomes, (void**) &_Biome$initBiomes);
	MSHookFunction((void*) &Dimension::createNew, (void*) &Dimension$createNew, (void**) &_Dimension$createNew);
	MSHookFunction((void*) &Dimension::_createGenerator, (void*) &Dimension$_createGenerator, (void**) &_Dimension$_createGenerator);
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	void* handle = (void*) dlopen("libminecraftpe.so", RTLD_LAZY);

	setupHooks(handle);

	return JNI_VERSION_1_2;
}
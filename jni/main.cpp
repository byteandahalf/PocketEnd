#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <substrate.h>

#include <memory>
#include <cmath>
#include <GLES/gl.h>

#include "com/mojang/minecraftpe/client/renderer/MatrixStack.h"
#include "com/mojang/minecraftpe/client/renderer/RenderContext.h"
#include "com/mojang/minecraftpe/client/renderer/TextureLocation.h"
#include "com/mojang/minecraftpe/client/renderer/LevelRenderer.h"
#include "com/mojang/minecraftpe/client/renderer/Tessellator.h"
#include "com/mojang/minecraftpe/client/renderer/Color.h"
#include "com/mojang/minecraftpe/client/renderer/ShaderColor.h"
#include "com/mojang/minecraftpe/client/renderer/entity/EntityRenderDispatcher.h"
#include "com/mojang/minecraftpe/client/MinecraftClient.h"
#include "com/mojang/minecraftpe/util/Math.h"
#include "com/mojang/minecraftpe/world/phys/Vec3.h"
#include "com/mojang/minecraftpe/world/dimension/NormalDimension.h"
#include "com/mojang/minecraftpe/world/dimension/HellDimension.h"
#include "com/mojang/minecraftpe/world/gen/RandomLevelSource.h"
#include "com/mojang/minecraftpe/world/gen/FlatLevelSource.h"
#include "com/mojang/minecraftpe/world/gen/HellRandomLevelSource.h"
#include "com/mojang/minecraftpe/world/level/Level.h"

#include "com/byteandahalf/pocketend/dimension/EndDimension.h"
#include "com/byteandahalf/pocketend/worldgen/EndRandomLevelSource.h"
#include "com/byteandahalf/pocketend/biome/TheEndBiome.h"
#include "com/byteandahalf/pocketend/entity/render/DragonRenderer.h"


void tiny_hook(uint32_t*, uint32_t);


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

static mce::Mesh skyMesh;

static void (*_LevelRenderer$_buildSkyMesh)(LevelRenderer*);
static void LevelRenderer$_buildSkyMesh(LevelRenderer* self)
{
	Tessellator& tessellator = Tessellator::instance;

	tessellator.begin(mce::PrimitiveMode::PRIMITIVEMODE_ONE, 4);

	tessellator.color(0x181818);
	tessellator.vertexUV(-100.0F, -100.0F, -100.0F, 0.0F, 0.0F);
	tessellator.vertexUV(-100.0F, -100.0F, 100.0F, 0.0F, 1.0F);
	tessellator.vertexUV(100.0F, -100.0F, 100.0F, 1.0F, 1.0F);
	tessellator.vertexUV(100.0F, -100.0F, -100.0F, 1.0F, 0.0F);
	skyMesh = tessellator.end(NULL, false);
}

static void (*_LevelRenderer$renderSky)(LevelRenderer*, Entity&, float);
static void LevelRenderer$renderSky(LevelRenderer* self, Entity& cameraEntity, float partialTicks)
{
	glDepthMask(false);

	self->sunTexture = mce::TexturePtr(self->minecraft.getTextures(), "environment/end_sky.png", TextureLocation::TEXLOC_ZERO);

	for(int i = 0; i < 5; i++)
	{
		MatrixStack::Ref projection = MatrixStack::View.push();
		if(i == 0)
		{
			projection.matrix.rotate(90.0F, {1.0F, 0.0F, 0.0});
		}
		if(i == 1)
		{
			projection.matrix.rotate(-90.0F, {1.0F, 0.0F, 0.0});
		}
		if(i == 2)
		{
			projection.matrix.rotate(180.0F, {1.0F, 0.0F, 0.0});
		}
		if(i == 3)
		{
			projection.matrix.rotate(90.0F, {0.0F, 0.0F, 1.0});
		}
		if(i == 4)
		{
			projection.matrix.rotate(-90.0F, {0.0F, 0.0F, 1.0F});
		}

		skyMesh.render(self->skyMaterial, self->sunTexture, 0, 0);
		projection.release();
	}

	glDepthMask(true);
}

static EntityRenderDispatcher* (*_EntityRenderDispatcher$C2)(EntityRenderDispatcher*, MinecraftClient&);
static EntityRenderDispatcher* EntityRenderDispatcher$C2(EntityRenderDispatcher* self, MinecraftClient& minecraft)
{
	_EntityRenderDispatcher$C2(self, minecraft);

	DragonRenderer::singleton = new DragonRenderer(minecraft.getTextures());
}

static EntityRenderer* (*_EntityRenderDispatcher$getRenderer)(EntityRenderDispatcher*, int);
static EntityRenderer* EntityRenderDispatcher$getRenderer(EntityRenderDispatcher* self, int rendererId)
{
	if(rendererId == 75)
	{
		return DragonRenderer::singleton;
	}
	return self->renderers[rendererId];
}

static void setupHooks(void* handle)
{
	MSHookFunction((void*) &Biome::initBiomes, (void*) &Biome$initBiomes, (void**) &_Biome$initBiomes);
	MSHookFunction((void*) &Dimension::createNew, (void*) &Dimension$createNew, (void**) &_Dimension$createNew);
	MSHookFunction((void*) &Dimension::_createGenerator, (void*) &Dimension$_createGenerator, (void**) &_Dimension$_createGenerator);
	//MSHookFunction((void*) &LevelRenderer::_buildSkyMesh, (void*) &LevelRenderer$_buildSkyMesh, (void**) &_LevelRenderer$_buildSkyMesh);
	//MSHookFunction((void*) &LevelRenderer::renderSky, (void*) &LevelRenderer$renderSky, (void**) &_LevelRenderer$renderSky);
	//MSHookFunction((void*) &EntityRenderDispatcher::getRenderer, (void*) &EntityRenderDispatcher$getRenderer, (void**) &_EntityRenderDispatcher$getRenderer);

	void* __EntityRenderDispatcher$C2 = (void*) dlsym(handle, "_ZN22EntityRenderDispatcherC2ER15MinecraftClient");
	MSHookFunction(__EntityRenderDispatcher$C2, (void*) &EntityRenderDispatcher$C2, (void**) &_EntityRenderDispatcher$C2);
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	void* handle = (void*) dlopen("libminecraftpe.so", RTLD_LAZY);

	setupHooks(handle);

	return JNI_VERSION_1_2;
}
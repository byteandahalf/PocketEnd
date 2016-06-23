#pragma once

struct Vec3;
struct Vec2;
struct Options;
namespace mce { struct TextureGroup; };
#include "../TexturePtr.h"

#include "EntityShaderManager.h"

struct EntityRenderer
: public EntityShaderManager
{
	EntityRenderer(mce::TextureGroup&, bool);

	bool bool1; // 40
	int int1; // 44
	mce::MaterialPtr materialAlphatest; // 48
	mce::MaterialPtr materialGlint; // 60
	mce::TexturePtr textureTerrainAtlas; // 72
	mce::TexturePtr textureGlint; // 88
	mce::MaterialPtr materialNameTag; // 104
	mce::MaterialPtr materialNameTagDepth; // 116
	mce::MaterialPtr materialNameText; // 128	

	virtual void render(Entity&, const Vec3&, float, float) = 0;
	virtual void postRender(Entity&, const Vec3&, float, float);
	virtual void renderDebug(Entity&, Options&);
	virtual void renderWaterHole(Entity&, const Vec3&, const Vec2&, float);
};

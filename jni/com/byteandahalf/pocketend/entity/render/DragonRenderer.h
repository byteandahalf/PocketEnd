#pragma once

#include "com/mojang/minecraftpe/client/renderer/entity/EntityRenderer.h"

struct DragonRenderer
: public EntityRenderer
{
	static DragonRenderer* singleton;

	DragonRenderer(mce::TextureGroup&);

	virtual void render(Entity&, const Vec3&, float, float);
};

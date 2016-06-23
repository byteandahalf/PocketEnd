
#include "DragonRenderer.h"

DragonRenderer* DragonRenderer::singleton = nullptr;

DragonRenderer::DragonRenderer(mce::TextureGroup& textures)
: EntityRenderer(textures, false){
}

void DragonRenderer::render(Entity& dragon, const Vec3& pos, float f, float f1)
{
	
}

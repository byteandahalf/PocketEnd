#pragma once

namespace mce
{
	struct TextureGroup;
};

struct MinecraftClient
{
	mce::TextureGroup& getTextures() const;
};

#pragma once

#include <string>
#include "TextureLocation.h"

namespace mce
{
	struct TextureGroup;
	struct TexturePtr
	{
		mce::TextureGroup& textures; // 0
		int idk; // 4
		std::string path; // 8
		TextureLocation location; // 12

		TexturePtr();
		TexturePtr(TexturePtr&&);
		TexturePtr(mce::TextureGroup&, const std::string&, TextureLocation);

		//~TexturePtr();

		TexturePtr& operator=(TexturePtr&&);
	};
};

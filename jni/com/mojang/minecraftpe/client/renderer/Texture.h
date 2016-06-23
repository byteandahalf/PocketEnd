#pragma once

namespace mce
{
	struct RenderContext;

	struct Texture
	{
		int idk;

		void bindTexture(mce::RenderContext&, unsigned int, unsigned int) const;
	};
};

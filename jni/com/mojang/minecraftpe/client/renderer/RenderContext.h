#pragma once

namespace mce
{
	struct RenderContext
	{
		char filler[4];

		void setDepthRange(float, float);
	};

	struct RenderContextImmediate
	: public RenderContext
	{
		static RenderContext& get();
	};
};

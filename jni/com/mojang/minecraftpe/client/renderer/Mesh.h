#pragma once

namespace mce
{
	struct MaterialPtr;
	struct TexturePtr;
	struct Mesh
	{
		char filler[84];

		void render(const mce::MaterialPtr&, unsigned int, unsigned int) const;
		void render(const mce::MaterialPtr&, const mce::TexturePtr&, unsigned int, unsigned int) const;

		~Mesh();
		mce::Mesh& operator=(mce::Mesh&&);
	};
};

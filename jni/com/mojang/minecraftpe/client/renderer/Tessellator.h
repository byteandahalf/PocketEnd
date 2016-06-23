#pragma once

struct Color;
struct Vec3;

namespace mce
{
	enum class PrimitiveMode : int
	{
		PRIMITIVEMODE_ZERO,
		PRIMITIVEMODE_ONE,
		PRIMITIVEMODE_TWO
	};

	struct Mesh;
	struct MaterialPtr;
	struct TexturePtr;
};

struct Tessellator
{
	char filler[243];

	static Tessellator instance;

	void begin(int);
	void begin(mce::PrimitiveMode, int);
	void beginIndices(int);
	void clear();
	void color(int);
	void color(const Color&);
	void color(float, float, float, float);
	mce::Mesh end(const char*, bool);
	void triangle(unsigned int, unsigned int, unsigned int);
	void draw(const mce::MaterialPtr&);
	void draw(const mce::MaterialPtr&, const mce::TexturePtr&);
	void vertex(float, float, float);
	void vertexUV(float, float, float, float, float);
	void setRotationOffset(float, const Vec3&);
	void scale3d(float, float, float);
	void setOffset(float, float, float);
};

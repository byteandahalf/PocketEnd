#pragma once

struct Random;
struct Vec2;
struct Vec3;

struct PerlinNoise
{
	char filler[20];

	PerlinNoise(Random&, int, int);

	float* getRegion(float*, const Vec2&, int, int, const Vec2&, float) const;
	float* getRegion(float*, const Vec3&, int, int, int, const Vec3&) const;
};

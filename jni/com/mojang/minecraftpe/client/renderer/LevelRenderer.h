#pragma once

struct Entity;
struct Dimension;
struct MinecraftClient;

#include "MaterialPtr.h"
#include "TexturePtr.h"
#include "Mesh.h"
#include "Texture.h"

struct LevelRenderer
{
	char filler[456]; // 0
	Dimension& dimension; // 456
	char filler2[4932]; // 460
	mce::TexturePtr sunTexture; // 5392
	char filler3[264]; // 5408
	MinecraftClient& minecraft; // 5672
	char filler4[8]; // 5676
	float idk; // 5684
	char filler5[172]; // 5688
	mce::Mesh skyMesh; // 5860
	char filler6[1212]; // 5944
	mce::MaterialPtr skyMaterial; // 7156
	mce::MaterialPtr sunMaterial; // 7168
	char filler7[304]; // 7180
	mce::Texture texture; // 7484

	void renderSky(Entity&, float);
	void _buildSkyMesh();

	float getFov(float, bool);
	float _getProjectionAspectRatio();
	float getAmbientBrightness() const;
	float _skyDarkeningFactor();

	void _renderSunOrMoon(float, bool);
	void _renderStars(float);
};

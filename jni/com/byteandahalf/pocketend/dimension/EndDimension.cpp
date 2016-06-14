#include <cmath>

#include "EndDimension.h"


EndDimension::EndDimension(Level& level)
: Dimension(level, DimensionId::HELL)
{}

void EndDimension::init()
{
	Dimension::init();

	setCeiling(true);
}

float EndDimension::getTimeOfDay(int, float) const
{
	return 0.0F;
}

float EndDimension::getCloudHeight() const
{
	return 8.0F;
}

Color EndDimension::getFogColor(float multiplier) const
{
	int baseColor = 0xA080A0;

	float helper = cos(multiplier * 3.1415926536F * 2.0F) * 2.0F + 0.5F;
	if(helper < 0.0F)
	{
		helper = 0.0F;
	}
	if(helper > 1.0F)
	{
		helper = 1.0F;
	}
	float r = (baseColor >> 16 & 255) / 255.0F;
	float g = (baseColor >> 8 & 255) / 255.0F;
	float b = (baseColor & 255) / 255.0F;
	float a = 1.0F;
	r *= helper * 0.0F + 0.15F;
	g *= helper * 0.0F + 0.15F;
	b *= helper * 0.0F + 0.15F;

	return Color(r, g, b, a);
}

bool EndDimension::isNaturalDimension() const
{
	return false;
}

bool EndDimension::mayRespawn() const
{
	return false;
}

bool EndDimension::isValidSpawn(int x, int z) const
{
	return true;
}

bool EndDimension::isFoggyAt(int x, int z) const
{
	return true;
}

const std::string EndDimension::getName() const
{
	return "The End";
}

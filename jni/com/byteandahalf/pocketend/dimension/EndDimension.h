#pragma once

#include "com/mojang/minecraftpe/world/dimension/Dimension.h"

struct EndDimension
: public Dimension
{
	EndDimension(Level&);

	void init();
	float getTimeOfDay(int, float) const;
	float getCloudHeight() const;
	Color getFogColor(float) const;
	bool isNaturalDimension() const;
	bool mayRespawn() const;
	bool isValidSpawn(int, int) const;
	bool isFoggyAt(int, int) const;
	const std::string getName() const;
};

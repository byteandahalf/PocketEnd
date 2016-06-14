#pragma once

struct MobSpawnerData
{
	int randomWeight;
	int mobClassId;
	int minCount;
	int maxCount;

	MobSpawnerData(int randomWeight, int mobClassId, int minCount, int maxCount)
	: randomWeight(randomWeight), mobClassId(mobClassId), minCount(minCount), maxCount(maxCount) {}
};

#include "com/mojang/minecraftpe/world/phys/Vec.h"
#include "com/mojang/minecraftpe/world/chunk/LevelChunk.h"
#include "com/mojang/minecraftpe/world/chunk/ChunkPos.h"
#include "com/mojang/minecraftpe/world/gen/ChunkViewSource.h"
#include "com/mojang/minecraftpe/world/gen/algorithm/PerlinNoise.h"
#include "com/mojang/minecraftpe/world/biome/Biome.h"
#include "com/mojang/minecraftpe/world/level/BlockSource.h"
#include "com/mojang/minecraftpe/world/level/BlockPos.h"

#include <cmath>
#include <cstdlib>

#include "EndRandomLevelSource.h"

EndRandomLevelSource::EndRandomLevelSource(Level* level, Dimension* dimension, unsigned int seed)
: ChunkSource(level, dimension, 16),
	endRNG((long unsigned int) seed)
{
	this->level = level;
	this->dimension = dimension;

	noiseGenerators[0] = new PerlinNoise(endRNG, 16, 0);
	noiseGenerators[1] = new PerlinNoise(endRNG, 16, 0);
	noiseGenerators[2] = new PerlinNoise(endRNG, 8, 0);
	noiseGenerators[3] = new PerlinNoise(endRNG, 10, 0);
	noiseGenerators[4] = new PerlinNoise(endRNG, 16, 0);
}

EndRandomLevelSource::~EndRandomLevelSource()
{
	delete[] noiseGenerators;
}

float* EndRandomLevelSource::getHeights(float* densities, int x, int y, int z, int sizeX, int sizeY, int sizeZ)
{
	float d = 684.412F * 2.0F;
	float d1 = 684.412F;
	
	float noiseData1[297];
	float noiseData2[297];
	float noiseData3[297];
	float noiseData4[297];
	float noiseData5[297];

	noiseGenerators[3]->getRegion(noiseData4, {(float) x, (float) z}, sizeX, sizeZ, {1.121F, 1.121F}, 0.5F);
	noiseGenerators[4]->getRegion(noiseData5, {(float) x, (float) z}, sizeX, sizeZ, {200.0F, 200.0F}, 0.5F);
	noiseGenerators[2]->getRegion(noiseData1, {(float) x, (float) y, (float) z}, sizeX, sizeY, sizeZ, {d / 80.0F, d1 / 160.0F, d / 80.0F});
	noiseGenerators[0]->getRegion(noiseData2, {(float) x, (float) y, (float) z}, sizeX, sizeY, sizeZ, {d, d1, d});
	noiseGenerators[1]->getRegion(noiseData3, {(float) x, (float) y, (float) z}, sizeX, sizeY, sizeZ, {d, d1, d});
	int k1 = 0;
	int l1 = 0;
	for(int i2 = 0; i2 < sizeX; i2++)
	{
		for(int j2 = 0; j2 < sizeZ; j2++)
		{
			float d2 = (noiseData4[l1] + 256.0F) / 512.0F;
			if(d2 > 1.0F)
			{
			    d2 = 1.0F;
			}
			float d3 = noiseData5[l1] / 8000.0F;
			if(d3 < 0.0F)
			{
			    d3 = -d3 * 0.3F;
			}
			d3 = d3 * 3.0F - 2.0F;
			float f = (float) ((i2 + x) - 0) / 1.0F;
			float f1 = (float) ((j2 + z) - 0) / 1.0F;
			float f2 = 100.0F - sqrt(f * f + f1 * f1) * 8.0F;
			if(f2 > 80.0F)
			{
			    f2 = 80.0F;
			}
			if(f2 < -100.0F)
			{
			    f2 = -100.0F;
			}
			if(d3 > 1.0F)
			{
			    d3 = 1.0F;
			}
			d3 /= 8.0F;
			d3 = 0.0F;
			if(d2 < 0.0F)
			{
			    d2 = 0.0F;
			}
			d2 += 0.5F;
			d3 = (d3 * (float) sizeY) / 16.0F;
			l1++;
			float d4 = (float) sizeY / 2.0F;
			for(int k2 = 0; k2 < sizeY; k2++)
			{
				float d5 = 0.0F;
				float d6 = (((float) k2 - d4) * 8.0F) / d2;
				if(d6 < 0.0F)
				{
					d6 *= -1.0F;
				}
				float d7 = noiseData2[k1] / 512.0F;
				float d8 = noiseData3[k1] / 512.0F;
				float d9 = (noiseData1[k1] / 10.0F + 1.0F) / 2.0F;
				if(d9 < 0.0F)
				{
					d5 = d7;
				}
				else if(d9 > 1.0F)
				{
					d5 = d8;
				}
				else
				{
					d5 = d7 + (d8 - d7) * d9;
				}
				d5 -= 8.0F;
				d5 += f2;
				int l2 = 2;
				if(k2 > sizeY / 2 - l2)
				{
					float d10 = (float) (k2 - (sizeY / 2 - l2)) / 64.0F;
					if(d10 < 0.0F)
					{
						d10 = 0.0F;
					}
					if(d10 > 1.0F)
					{
						d10 = 1.0F;
					}
					d5 = d5 * (1.0F - d10) + -3000.0F * d10;
				}
				l2 = 8;
				if(k2 < l2)
				{
					float d11 = (float) (l2 - k2) / ((float) l2 - 1.0F);
					d5 = d5 * (1.0F - d11) + -30.0F * d11;
				}
				densities[k1] = d5;
				k1++;
			}
		}
	}

	return densities;
}

void EndRandomLevelSource::prepareHeights(int x, int z, LevelChunk& chunk)
{
	int i = 2;
	int j = i + 1;
	int k = 33;
	int l = i + 1;
	getHeights(densities, x * i, 0, z * i, j, k, l);
	uint8_t* rawBlocks = chunk.getRawBlocks();

	for(int i1 = 0; i1 < i; ++i1)
	{
		for(int j1 = 0; j1 < i; ++j1)
		{
			for(int k1 = 0; k1 < 32; ++k1)
			{
				float d0 = 0.25F;
				float d1 = densities[((i1 + 0) * l + j1 + 0) * k + k1 + 0];
				float d2 = densities[((i1 + 0) * l + j1 + 1) * k + k1 + 0];
				float d3 = densities[((i1 + 1) * l + j1 + 0) * k + k1 + 0];
				float d4 = densities[((i1 + 1) * l + j1 + 1) * k + k1 + 0];
				float d5 = (densities[((i1 + 0) * l + j1 + 0) * k + k1 + 1] - d1) * d0;
				float d6 = (densities[((i1 + 0) * l + j1 + 1) * k + k1 + 1] - d2) * d0;
				float d7 = (densities[((i1 + 1) * l + j1 + 0) * k + k1 + 1] - d3) * d0;
				float d8 = (densities[((i1 + 1) * l + j1 + 1) * k + k1 + 1] - d4) * d0;

				for(int l1 = 0; l1 < 4; ++l1)
				{
					float d9 = 0.125F;
					float d10 = d1;
					float d11 = d2;
					float d12 = (d3 - d1) * d9;
					float d13 = (d4 - d2) * d9;

					for(int i2 = 0; i2 < 8; ++i2)
					{
						int currentBlock = i2 + i1 * 8 << 11 | 0 + j1 * 8 << 7 | k1 * 4 + l1;
			    		int worldHeightLimit = 1 << 7;
			    		float d14 = 0.125F;
			    		float d15 = d10;
			    		float d16 = (d11 - d10) * d14;

						for(int j2 = 0; j2 < 8; ++j2)
						{
							int j3 = 0;
							if(d15 > 0.0F)
							{
							    j3 = 121;//Block::mEndStone->blockId;
							}
							rawBlocks[currentBlock] = (uint8_t) j3;
							currentBlock += worldHeightLimit;
							d15 += d16;
						}

						d10 += d12;
						d11 += d13;
					}

					d1 += d5;
					d2 += d6;
					d3 += d7;
					d4 += d8;
				}
			}
		}
	}
}

void EndRandomLevelSource::buildSurfaces(LevelChunk& chunk, ChunkPos chunkPos)
{
	uint8_t* rawBlocks = chunk.getRawBlocks();
	for(int k = 0; k < 16; k++)
	{
		for(int l = 0; l < 16; l++)
		{
			int i1 = 1;
			int j1 = -1;
			int byte0 = 121;//Block::mEndStone->blockId;
			int byte1 = 121;//Block::mEndStone->blockId;
			for(int k1 = 127; k1 >= 0; k1--)
			{
				int l1 = (l * 16 + k) * 128 + k1;
				int byte2 = rawBlocks[l1];
				if(byte2 == 0)
				{
					j1 = -1;
					continue;
				}
				if(byte2 != 1)//Block::mStone->blockId
				{
					continue;
				}
				if(j1 == -1)
				{
					if(i1 <= 0)
					{
						byte0 = 0;
						byte1 = 121;//Block::mEndStone->blockId;
					}
					j1 = i1;
					if(k1 >= 0)
					{
						rawBlocks[l1] = byte0;
					}
					else
					{
						rawBlocks[l1] = byte1;
					}
					continue;
				}
				if(j1 > 0)
				{
					j1--;
					rawBlocks[l1] = byte1;
				}
			}
		}
	}
}

LevelChunk* EndRandomLevelSource::requestChunk(const ChunkPos& pos, ChunkSource::LoadMode mode)
{
	if(mode == ChunkSource::LoadMode::NONE)
	{
		return NULL;
	}

	return new LevelChunk(*level, *dimension, pos, false);
}

void EndRandomLevelSource::loadChunk(LevelChunk& chunk)
{
	ChunkPos chunkPos = chunk.getPosition();
	endRNG.setSeed(chunkPos.x * 0x9939f508 + chunkPos.z * 0xf1565bd5);

	for(int i = 0; i < 16; i++)
	{
		for(int k = 0; k < 16; k++)
		{
			chunk.setBiome(Biome::getBiome(Biome::sky->biomeId), {i, k, 0});
		}
	}

	prepareHeights(chunkPos.x, chunkPos.z, chunk);
	buildSurfaces(chunk, chunkPos);
	chunk.recalcHeightmap();

	chunk.setGenerator(this);
	chunk.setUnsaved();
	chunk.changeState(ChunkState::CHUNKSTATE_1, ChunkState::CHUNKSTATE_2);
}

void EndRandomLevelSource::postProcess(ChunkViewSource& view)
{
	ChunkViewSource::ViewArea area = view.getArea();
	BlockSource region(getLevel(), getDimension(), view, false, true);
	Biome::sky->decorate(&region, endRNG, getExistingChunk({area.posX, area.posZ}), {area.posX, area.posZ}, 0.0F);
}

/*std::vector<Mob*> EndRandomLevelSource::getMobsAt(BlockSource& region, EntityType type, const BlockPos& pos)
{
	return Biome::EMPTY_MOBLIST;
}*/

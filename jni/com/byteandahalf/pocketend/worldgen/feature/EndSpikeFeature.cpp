#include "com/mojang/minecraftpe/util/Random.h"
#include "com/mojang/minecraftpe/world/level/BlockPos.h"
#include "com/mojang/minecraftpe/world/level/BlockSource.h"

#include "EndSpikeFeature.h"

EndSpikeFeature::EndSpikeFeature(int groundBlock)
: Feature(true), groundBlock(groundBlock) {}

bool EndSpikeFeature::place(BlockSource& region, const BlockPos& pos, Random& rng)
{
	int i = pos.x, j = pos.y, k = pos.z;
	if (!region.isEmptyBlock(pos) || region.getBlockID({i, j - 1, k}) != groundBlock)
	{
	    return false;
	}
	int l = rng.nextInt(32) + 6;
	int i1 = rng.nextInt(4) + 1;
	for (int j1 = i - i1; j1 <= i + i1; j1++)
	{
	    for (int l1 = k - i1; l1 <= k + i1; l1++)
	    {
	        int j2 = j1 - i;
	        int l2 = l1 - k;
	        if (j2 * j2 + l2 * l2 <= i1 * i1 + 1 && region.getBlockID({j1, j - 1, l1}) != groundBlock)
	        {
	            return false;
	        }
	    }
	}

	for (int k1 = j; k1 < j + l && k1 < 128; k1++)
	{
	    for (int i2 = i - i1; i2 <= i + i1; i2++)
	    {
	        for (int k2 = k - i1; k2 <= k + i1; k2++)
	        {
	            int i3 = i2 - i;
	            int j3 = k2 - k;
	            if (i3 * i3 + j3 * j3 <= i1 * i1 + 1)
	            {
	                region.setBlock({i2, k1, k2}, BlockID{49}, 2);
	            }
	        }
	    }
	}

	/*EntityEnderCrystal entityendercrystal = new EntityEnderCrystal(world);
	entityendercrystal.setLocationAndAngles((float)i + 0.5F, j + l, (float)k + 0.5F, random.nextFloat() * 360F, 0.0F);
	world.spawnEntityInWorld(entityendercrystal);
	world.setBlockWithNotify(i, j + l, k, Block.bedrock.blockID);*/
	return true;
}

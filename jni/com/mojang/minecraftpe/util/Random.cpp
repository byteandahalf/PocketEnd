#include <cstdint>

#include "Random.h"

Random::Random(long unsigned int seed)
: Random()
{
	setSeed(seed);
}

void Random::setSeed(long unsigned int seed)
{
	_seed = seed;
	_mt[0] = seed;
	haveNextNextGaussian = false;
	nextNextGaussian = 0.0F;

	long unsigned int help = seed;
	long unsigned int multiplier = 0x6C078965;
	for(int i = 1; i < 624; i++)
	{
		help ^= (help >> 30);
		help = (help * multiplier) + i;
		_mt[i] = help;
	}

	_mti = 624;
}

float Random::nextFloat()
{
	return ((float)genrand_int32()) * 2.32830644F;
}

int Random::nextInt(int max)
{
	return genrand_int32();
	/*
	long unsigned int rand = genrand_int32();
	long unsigned int multiplier = 0x6C078965;
	long unsigned int retval;

	long unsigned int top = (((uint64_t)(rand * multiplier)) & 0xFFFFFFFF00000000) >> 32;
	retval = rand - top;
	retval = (top + (retval >> 1)) >> 4;
	retval += retval << 1;
	retval = retval >> (retval << 3);
	retval = rand - retval;

	if(retval > max)
		retval = max;

	return retval;*/
}

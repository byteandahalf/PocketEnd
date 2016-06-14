#pragma once

struct BlockSource;
struct BlockPos;
struct Random;

struct BiomeDecorator
{
	char filler[252];

	BiomeDecorator();

	virtual void decorateOres(BlockSource*, Random&, const BlockPos&);
	virtual ~BiomeDecorator();
};

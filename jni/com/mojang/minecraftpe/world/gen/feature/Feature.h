#pragma once

struct BlockSource;
struct BlockPos;
struct Random;

struct Feature
{
	char filler[12];

	Feature(bool);

	virtual ~Feature();
	virtual bool place(BlockSource&, const BlockPos&, Random&) = 0;
};

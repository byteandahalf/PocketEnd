#pragma once

struct BlockSource;
struct BlockPos;
struct FullBlock;
struct BlockEntity;
struct Entity;

#include <memory> // for unique_ptr

struct BlockSourceListener
{
	virtual ~BlockSourceListener();
	virtual void onSourceCreated(BlockSource&);
	virtual void onSourceDestroyed(BlockSource&);
	virtual void onBlocksDirty(BlockSource&, int, int, int, int, int, int);
	virtual void onAreaChanged(BlockSource&, const BlockPos&, const BlockPos&);
	virtual void onBlockChanged(BlockSource&, const BlockPos&, FullBlock, FullBlock, int);
	virtual void onBrightnessChanged(BlockSource&, const BlockPos&);
	virtual void onBlockEntityChanged(BlockSource&, BlockEntity&);
	virtual void onEntityChanged(BlockSource&, Entity&);
	virtual void onBlockEntityRemoved(BlockSource&, std::unique_ptr<BlockEntity>);
	virtual void onBlockEvent(BlockSource&, int, int, int, int, int);
};

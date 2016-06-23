#pragma once

#include "com/mojang/minecraftpe/world/entity/Entity.h"

struct EnderDragon
: public Entity // TODO: Animal
{
	EnderDragon(BlockSource&, float, float, float);

	virtual EntityType getEntityTypeId() const;
	virtual void readAdditionalSaveData(const CompoundTag&);
	virtual void addAdditionalSaveData(CompoundTag&);
};


#include "EnderDragon.h"

EnderDragon::EnderDragon(BlockSource& region, float x, float y, float z)
:	Entity(region)
{
	rendererId = 75;
	yOffset = heightOffset / 2.0F;
	setSize(1.0F, 1.0F);
	setPos({x, y, z});
	_init();
}

EntityType EnderDragon::getEntityTypeId() const
{
	return EntityType::DRAGON;
}

void EnderDragon::readAdditionalSaveData(const CompoundTag& data)
{

}

void EnderDragon::addAdditionalSaveData(CompoundTag& data)
{

}

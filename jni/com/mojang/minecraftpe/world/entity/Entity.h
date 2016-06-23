#pragma once

#include <string>
#include <memory>
#include <vector>

struct BlockSource;
struct Level;
struct Material;
struct Player;
struct EntityPos;
struct EntityLocation;
struct BlockPos;
struct FullBlock;
struct MaterialType;
struct Vec2;
struct CompoundTag;
struct EntityLink;
struct EntityDamageSource;
struct EntityEvent;
struct ItemInstance;
struct ChangeDimensionPacket;
struct ArmorSlot;
struct AABB;
#include "EntityType.h"
#include "../phys/Vec3.h"
#include "../phys/Vec2.h"
#include "../dimension/DimensionId.h"

struct Entity
{
	/* constructors */
	Entity(BlockSource&);
	Entity(Level&);

	/* member functions */
	void _init();
	void enableAutoSendPosRot(bool);
	void setRot(const Vec2&);

	/* fields */
	void* idk; // 4
	Vec3 pos; // 8
	Vec3 oldPos; // 20
	Vec3 chunkPos; // 32
	Vec3 velocity; // 44
	Vec2 rotation; // 56
	Vec2 oldRotation; // 64
	char filler[48]; // 72
	Level& level; // 120
	char filler2[52]; // 124
	float yOffset; // 176
	char filler3[12]; // 180
	float heightOffset; // 192
	char filler4[64]; // 196
	int rendererId; // 260
	std::vector<Entity*> _riders; // 264
	Entity& immediateRider; // 276
	Entity& riding; // 280
	char filler5[80]; // 284
	BlockSource& region; // 364

	/* vtable */
	virtual ~Entity();
	virtual void _postInit();
	virtual void reset();
	virtual int getOwnerEntityType();
	virtual void remove();
	virtual void setPos(const Vec3&);
	virtual Vec3& getPos() const;
	virtual Vec3& getPosOld() const;
	virtual Vec3& getPosExtrapolated(float) const;
	virtual Vec3& getVelocity() const;
	virtual void move(const Vec3&);
	virtual void checkBlockCollisions(const AABB&);
	virtual void checkBlockCollisions();
	virtual void moveRelative(float, float, float);
	virtual void lerpTo(const Vec3&, const Vec2&, int);
	virtual void lerpMotion(const Vec3&);
	virtual void turn(const Vec2&, bool);
	virtual void interpolateTurn(const Vec2&);
	virtual void* getAddPacket();
	virtual void normalTick();
	virtual void baseTick();
	virtual void rideTick();
	virtual void* positionRider(Entity&) const;
	virtual float getRidingHeight();
	virtual float getRideHeight() const;
	virtual void startRiding(Entity&);
	virtual void addRider(Entity&);
	virtual void removeRider(Entity&);
	virtual bool intersects(const Vec3&, const Vec3&);
	virtual bool isFree(const Vec3&, float);
	virtual bool isFree(const Vec3&);
	virtual bool isInWall() const;
	virtual bool isInvisible();
	virtual bool canShowNameTag();
	virtual void setNameTagVisible(bool);
	virtual const std::string& getNameTag() const;
	virtual void setNameTag(const std::string&);
	virtual bool isInWater() const;
	virtual bool isInWaterOrRain();
	virtual bool isInLava();
	virtual bool isBaby() const;
	virtual bool isUnderLiquid(MaterialType) const;
	virtual void makeStuckInWeb();
	virtual float getHeadHeight() const;
	virtual float getShadowHeightOffs();
	virtual float getShadowRadius() const;
	virtual bool isSkyLit(float);
	virtual float getBrightness(float);
	virtual bool interactPreventDefault();
	virtual void interactWithPlayer(Player&);
	virtual bool canInteractWith(Player&);
	virtual std::string getInteractText(Player&);
	virtual void playerTouch(Player&);
	virtual void push(Entity&, bool);
	virtual void push(const Vec3&);
	virtual bool isImmobile() const;
	virtual bool isSilent();
	virtual bool isPickable();
	virtual bool isPushable() const;
	virtual bool isShootable();
	virtual bool isSneaking() const;
	virtual bool isAlive() const;
	virtual bool isOnFire() const;
	virtual bool isCreativeModeAllowed();
	virtual bool isSurfaceMob() const;
	virtual void hurt(const EntityDamageSource&, int);
	virtual void animateHurt();
	virtual void doFireHurt(int);
	virtual void onLightningHit();
	virtual void onBounceStarted(const BlockPos&, const FullBlock&);
	virtual void handleEntityEvent(EntityEvent);
	virtual int getPickRadius();
	virtual void spawnAtLocation(int, int);
	virtual void spawnAtLocation(int, int, float);
	virtual void spawnAtLocation(const ItemInstance&, float);
	virtual void awardKillScore(Entity&, int);
	virtual void setEquippedSlot(ArmorSlot, int, int);
	virtual void setEquippedSlot(ArmorSlot, const ItemInstance&);
	virtual void save(CompoundTag&);
	virtual void saveWithoutId(CompoundTag&);
	virtual void load(const CompoundTag&);
	virtual void loadLinks(const CompoundTag&, std::vector<EntityLink>&);
	virtual EntityType getEntityTypeId() const = 0;
	virtual void queryEntityRenderer();
	virtual long getSourceUniqueID();
	virtual void setOnFire(int);
	virtual AABB getHandleWaterAABB() const;
	virtual void handleInsidePortal(const BlockPos&);
	virtual int getPortalCooldown() const;
	virtual int getPortalWaitTime() const;
	virtual DimensionId getDimensionId() const;
	virtual void changeDimension(DimensionId);
	virtual void changeDimension(ChangeDimensionPacket&);
	virtual Player* getControllingPlayer() const;
	virtual void checkFallDamage(float, bool);
	virtual void causeFallDamage(float);
	virtual void playSound(const std::string&, float, float, EntityLocation);
	virtual void onSynchedDataUpdate(int);
	virtual bool canAddRider(Entity&) const;
	virtual float getEyeHeight() const;
	virtual void sendMotionPacketIfNeeded();
	virtual void stopRiding(bool);
	virtual void buildDebugInfo(std::string&) const;
	virtual bool hasOutputSignal(signed char) const;
	virtual int getOutputSignal() const;
	virtual std::string getDebugText(std::vector<std::string>&);
	virtual void setSize(float, float);
	virtual void setPos(const EntityPos&);
	virtual void outOfWorld();
	virtual void markHurt();
	virtual void burn(int);
	virtual void lavaHurt();
	virtual void readAdditionalSaveData(const CompoundTag&) = 0;
	virtual void addAdditionalSaveData(CompoundTag&) = 0;
	virtual void _playStepSound(const BlockPos&, int);
	virtual void checkInsideBlocks(float);
	virtual void pushOutOfBlocks(const Vec3&);
	virtual void updateWaterState();
	virtual void doWaterSplashEffect();
	virtual void updateInsideBlock();
	virtual void onBlockCollision(int);
};

typedef std::vector<Entity*> EntityList;

#include "CollisionHandler.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "GameObject/Bullets/Bullet.h"
#include "GameObject/Zombies/Zombie.h"
#include "GameObject/Plants/Plant.h"
#include "GameObject/Zombies/RegularZombie.h"
#include "GameObject/Zombies/ShootingZombie.h"
#include "GameObject/Plants/ShootingPlant.h"
#include "GameObject/Plants/ResourcePlant.h"
#include "GameObject/Plants/TrapPlant.h"
#include "GameObject/Plants/WallPlant.h"

namespace
{
	void zombieHitsPlant(GameObject& zombieObj, GameObject& plantObj)
	{
		auto& zombie = static_cast<Zombie&>(zombieObj);
		auto& plant = static_cast<Plant&>(plantObj);
		zombie.onCollisionWithPlant(&plant);
	}

	void plantBulletHitsZombie(GameObject& bulletObj, GameObject& zombieObj)
	{
		auto& bullet = static_cast<PlantBullet&>(bulletObj);
		auto& zombie = static_cast<Zombie&>(zombieObj);
		bullet.onHit(zombie);
	}

	void zombieBulletHitsPlant(GameObject& bulletObj, GameObject& plantObj)
	{
		auto& bullet = static_cast<ZombieBullet&>(bulletObj);
		auto& plant = static_cast<Plant&>(plantObj);
		bullet.onHit(plant);
	}

	void zombieTrap(GameObject& zombieObj, GameObject& trapObj)
	{
		auto& zombie = static_cast<Zombie&>(zombieObj);
		auto& trap = static_cast<TrapPlant&>(trapObj);
		trap.handleCollision(zombie);
	}

	void zombieBullet(GameObject& zombie, GameObject& bullet) { plantBulletHitsZombie(bullet, zombie); }
	void plantBullet(GameObject& plant, GameObject& bullet) { zombieBulletHitsPlant(bullet, plant); }
	void plantZombie(GameObject& plant, GameObject& zombie) { zombieHitsPlant(zombie, plant); }
	void trapZombie(GameObject& trap, GameObject& zombie) { zombieTrap(zombie, trap); }

	using HitFunctionPtr = void (*)(GameObject&, GameObject&);
	using Key = std::pair<std::type_index, std::type_index>;
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;

		phm[Key(typeid(PlantBullet), typeid(RegularZombie))]    = &plantBulletHitsZombie;
		phm[Key(typeid(RegularZombie), typeid(PlantBullet))]    = &zombieBullet;
		phm[Key(typeid(PlantBullet), typeid(ShootingZombie))]   = &plantBulletHitsZombie;
		phm[Key(typeid(ShootingZombie), typeid(PlantBullet))]   = &zombieBullet;
		phm[Key(typeid(ZombieBullet), typeid(ShootingPlant))]   = &zombieBulletHitsPlant;
		phm[Key(typeid(ShootingPlant), typeid(ZombieBullet))]   = &plantBullet;
		phm[Key(typeid(ZombieBullet), typeid(ResourcePlant))]   = &zombieBulletHitsPlant;
		phm[Key(typeid(ResourcePlant), typeid(ZombieBullet))]   = &plantBullet;
		phm[Key(typeid(ZombieBullet), typeid(WallPlant))]       = &zombieBulletHitsPlant;
		phm[Key(typeid(WallPlant), typeid(ZombieBullet))]       = &plantBullet;
		phm[Key(typeid(RegularZombie), typeid(ResourcePlant))]  = &zombieHitsPlant;
		phm[Key(typeid(ResourcePlant), typeid(RegularZombie))]  = &plantZombie;
		phm[Key(typeid(RegularZombie), typeid(ShootingPlant))]  = &zombieHitsPlant;
		phm[Key(typeid(ShootingPlant), typeid(RegularZombie))]  = &plantZombie;
		phm[Key(typeid(RegularZombie), typeid(WallPlant))]      = &zombieHitsPlant;
		phm[Key(typeid(WallPlant), typeid(RegularZombie))]      = &plantZombie;
		phm[Key(typeid(ShootingZombie), typeid(ResourcePlant))] = &zombieHitsPlant;
		phm[Key(typeid(ResourcePlant), typeid(ShootingZombie))] = &plantZombie;
		phm[Key(typeid(ShootingZombie), typeid(ShootingPlant))] = &zombieHitsPlant;
		phm[Key(typeid(ShootingPlant), typeid(ShootingZombie))] = &plantZombie;
		phm[Key(typeid(ShootingZombie), typeid(WallPlant))]     = &zombieHitsPlant;
		phm[Key(typeid(WallPlant), typeid(ShootingZombie))]     = &plantZombie;
		phm[Key(typeid(TrapPlant), typeid(ShootingZombie))]     = &trapZombie;
		phm[Key(typeid(ShootingZombie), typeid(TrapPlant))]     = &zombieTrap;
		phm[Key(typeid(TrapPlant), typeid(RegularZombie))]      = &trapZombie;
		phm[Key(typeid(RegularZombie), typeid(TrapPlant))]      = &zombieTrap;

		return phm;
	}

	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end()) return nullptr;
		return mapEntry->second;
	}
}

void processCollision(GameObject& object1, GameObject& object2)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (phf) phf(object1, object2);
}

UnknownCollision::UnknownCollision(GameObject& a, GameObject& b)
	: std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name())
{
}
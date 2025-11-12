#include "GameObject/Zombies/RegularZombie.h"

#include "Managers/TextureManager.h"
#include <Strategy/Movement/LinearMovementStrategy.h>
#include <Strategy/ZombieTrapResponse/DefaultResponseStrategy.h>
#include <Strategy/ZombieTrapResponse/InstaKillResponseStrategy.h>

namespace {
	auto move = []() { return std::make_unique<LinearMovementStrategy>(); };
	auto res = []() {return std::make_unique<DefaultResponseStrategy>(); };

	bool ok =
		GameObject::registerType<RegularZombie>(ZombieData::regularZombie, move, res) &&
		GameObject::registerType<RegularZombie>(ZombieData::bucketheadZombie, move, res) &&
		GameObject::registerType<RegularZombie>(ZombieData::coneheadZombie, move, res) &&
		GameObject::registerType<RegularZombie>(ZombieData::flagZombie, move, res) &&
		GameObject::registerType<RegularZombie>(ZombieData::zomboni, move, []() {return std::make_unique< InstaKillResponseStrategy>(); });
}

RegularZombie::RegularZombie(const CreationParams& p, const ZombieData::Definition& def,
	std::unique_ptr<IMovementStrategy> moveStrategy, std::unique_ptr<ITrapResponseStrategy> trapResponseStrategy)
	: Zombie(def, p, std::move(moveStrategy), std::move(trapResponseStrategy))
{}
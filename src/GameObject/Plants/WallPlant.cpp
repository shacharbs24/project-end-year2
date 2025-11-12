#include "GameObject/Plants/WallPlant.h"

namespace {
	bool ok =
		GameObject::registerType<WallPlant>(PlantData::wallPotato) &&
		GameObject::registerType<WallPlant>(PlantData::tallNut);
}

WallPlant::WallPlant(const CreationParams& p, const PlantData::Definition& def)
	: Plant(def, p)
{
}
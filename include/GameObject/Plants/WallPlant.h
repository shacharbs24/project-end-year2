#pragma once
#include "Plant.h"

class WallPlant : public Plant {
public:
	WallPlant(const CreationParams& p, const PlantData::Definition& def);
};
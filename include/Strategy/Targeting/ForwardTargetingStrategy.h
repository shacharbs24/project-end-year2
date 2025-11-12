#pragma once
#include "Strategy/Targeting/ITargetingStrategy.h"

class ForwardTargetingStrategy : public ITargetingStrategy {
public:
    bool shouldShoot(const Plant& plant, const TargetingSystem& system) const override;
};
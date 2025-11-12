#pragma once

class Plant;
class TargetingSystem;

class ITargetingStrategy {
public:
    virtual ~ITargetingStrategy() = default;
    virtual bool shouldShoot(const Plant& plant, const TargetingSystem& system) const = 0;
};
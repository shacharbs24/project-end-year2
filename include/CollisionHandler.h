#pragma once

#include <stdexcept>

class GameObject;

void processCollision(GameObject& object1, GameObject& object2);

class UnknownCollision : public std::runtime_error
{
public:
	UnknownCollision(GameObject& a, GameObject& b);
};
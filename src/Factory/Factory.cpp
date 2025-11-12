#include "Factory/Factory.h"
#include "GameObject/GameObject.h"

std::unique_ptr<GameObject> Factory::create(const std::string& name, const CreationParams& params)
{
	auto it = getMap().find(name);
	if (it == getMap().end()) throw std::runtime_error("Factory: Unknown id '" + name + "'");
	return it->second(params);
}

bool Factory::registerit(const std::string& name, Creator creator)
{
	getMap().emplace(name, std::move(creator));
	return true;
}
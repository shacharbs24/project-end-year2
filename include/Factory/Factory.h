#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>
#include "CreationParams.h"

class GameObject;

class Factory
{
public:
	using Creator = std::function<std::unique_ptr<GameObject>(const CreationParams&)>;
	using creatorMap = std::unordered_map<std::string, Creator>;

	static std::unique_ptr<GameObject> create(const std::string& id, const CreationParams& params);
	static bool registerit(const std::string& name, Creator creator);

private:
	static creatorMap& getMap()
	{
		static creatorMap map;
		return map;
	}
};

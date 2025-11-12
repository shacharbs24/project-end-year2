#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <Button/Button.h>

struct PlantButtonData
{
	std::string id;
	int cost;
	Button button;
	sf::Time cooldown;
	sf::Time cooldownRemaining = sf::Time::Zero;
	bool onCooldown = false;

	PlantButtonData(std::string _id, int _cost, sf::Time _cd, sf::Sprite spr, std::unique_ptr<ICommand> cmd);
	void draw(sf::RenderWindow& w) const;
	void updateVisualState(int sun);
	void startCooldown();
	void executeCommand();
	void handleClick(const sf::Event& e, int playerSun);
	void update(const sf::Time& dt, int sun);
};

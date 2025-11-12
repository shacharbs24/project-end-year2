#include "PlantButtonData.h"

PlantButtonData::PlantButtonData(std::string _id, int _cost, sf::Time _cd, sf::Sprite spr, std::unique_ptr<ICommand> cmd)
	: id(std::move(_id)), cost(_cost), cooldown(_cd), button(std::move(spr), std::move(cmd))
{
	startCooldown();
}

void PlantButtonData::updateVisualState(int sun)
{
	if (onCooldown || sun < cost)
		button.setSpriteColor(sf::Color(255, 255, 255, 128));
	else
		button.setSpriteColor(sf::Color::White);
}

void PlantButtonData::startCooldown()
{
	onCooldown = true;
	cooldownRemaining = cooldown;
}

void PlantButtonData::draw(sf::RenderWindow& w) const {
	button.draw(w);
}

void PlantButtonData::executeCommand() {
	button.executeCommand();
}

void PlantButtonData::handleClick(const sf::Event& e, int playerSun)
{
	if (playerSun < cost || onCooldown || !button.isClicked({ float(e.mouseButton.x), float(e.mouseButton.y) })) return;
	executeCommand();
}

void PlantButtonData::update(const sf::Time& dt, int sun)
{
	if (onCooldown)
	{
		cooldownRemaining -= dt;
		if (cooldownRemaining <= sf::Time::Zero)
		{
			onCooldown = false;
		}
	}

	updateVisualState(sun);
}
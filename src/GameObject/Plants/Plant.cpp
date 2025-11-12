#include "GameObject/Plants/Plant.h"
#include "Managers/TargetingSystem.h"
#include "UI/UIManager.h"
#include "Managers/AudioManager.h"


Plant::Plant(const PlantData::Definition& def, const CreationParams& params)
	: GameObject(params.position, TextureManager::getInstance().getTexture(def.sheet), def.spriteDef)
	, m_targetingSystem(*params.TargetingSystem)
	, m_uiManager(*params.UIManager)
	, m_board(*params.board)
	, m_health(def.health)
{
	m_targetingSystem.addPlant(*this);
	AudioManager::getInstance().playFx("plant");
	m_animation.setup(def.spriteDef.rect, def.frameCount, 0.2f, def.offset);
	m_currentAnimation = &m_animation;
}

Plant::~Plant()
{
	m_targetingSystem.removePlant(*this);
	notifyObservers();
}

void Plant::takeDamage(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		notifyObservers();
		die();
		m_board.clearCellAtPixel(getCenter());
	}
}


void Plant::handleEvent(const sf::Event& event)
{
	if (m_uiManager.isShovelSelected() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mousePos(float(event.mouseButton.x), float(event.mouseButton.y));
		if (m_sprite.getGlobalBounds().contains(mousePos))
		{
			AudioManager::getInstance().playFx("shovelout");
			die();
			m_uiManager.cancelSelection();
		}
	}
}

void Plant::update(const sf::Time& dt)
{
	updateAnimation(dt);
}

void Plant::addObserver(IObserver* observer)
{
	m_observers.push_back(observer);
}

void Plant::removeObserver(IObserver* observer)
{
	m_observers.remove(observer);
}

void Plant::notifyObservers()
{
	for (auto* observer : m_observers)
	{
		observer->onNotify(*this);
	}
}

void Plant::die()
{
	setToDelete(true);
	m_board.clearCellAtPixel(getCenter());
}
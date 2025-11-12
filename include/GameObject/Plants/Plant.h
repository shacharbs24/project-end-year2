#pragma once
#include "Config/PlantData.h"
#include "Factory/Factory.h"
#include "Observer/ISubject.h"
#include <memory>
#include <list>

class Iobserver;

class Plant : public GameObject, ISubject
{
public:
	Plant(const PlantData::Definition& def, const CreationParams& params);
	virtual ~Plant() override;

	void takeDamage(int damage) override;

	void update(const sf::Time& dt);
	void handleEvent(const sf::Event& event) override;

	void addObserver(IObserver* observer) override;
	void removeObserver(IObserver* observer) override;
	void notifyObservers() override;

	void die();

protected:
	TargetingSystem& m_targetingSystem;
	UIManager& m_uiManager;
	Board& m_board;
	std::list<IObserver*> m_observers;
private:
	int m_health;
	Animation m_animation;
};
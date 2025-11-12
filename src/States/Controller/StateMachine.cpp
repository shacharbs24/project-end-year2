#include "States/Controller/StateMachine.h"
#include "States/Controller/State.h"
#include <Command/MuteCommand.h>
#include <Managers/AudioManager.h>
#include <Command/PopStateCommand.h>
#include <Config/GameConfig.h>
#include <Managers/TextureManager.h>
#include <States/Controller/GameState.h>

StateMachine::StateMachine(sf::RenderWindow& win) : m_window(win),
m_muteButton(sf::Sprite(TextureManager::getInstance().getTexture("other_plants")), nullptr),
m_backButton({ 50, 50 }, { 100, 50 }, "Back", 40, std::make_unique<PopStateCommand>(*this))
{
	m_muteButton.setPosition({ float(window::width - 180.f), 10.f });
	m_muteButton.setTextureRect(AudioManager::getInstance().isMuted() ? sf::IntRect(486, 161, 53, 51) : sf::IntRect(551, 161, 53, 51));
	m_muteButton.setCommand(std::make_unique<MuteCommand>(m_muteButton));
}

void StateMachine::requestPop(size_t times)
{
	m_pendingPops += times;
}

void StateMachine::pop()
{
	if (!empty())
	{
		m_stack.pop_back();
		m_backButton.setTextColor(sf::Color::Black);
	}
}

void StateMachine::handleEvent(const sf::Event& e)
{
	if (!empty())
		m_stack.back()->handleEvent(e);
	m_muteButton.handleEvent(e);
}

void StateMachine::update(sf::Time dt)
{
	if (empty()) return;
	m_stack.back()->update(dt);

	for (size_t i = 0; i < m_pendingPops; ++i)
		pop();
	m_pendingPops = 0;

	if (m_pendingGameStatePush.has_value())
	{
		push<GameState>(m_pendingGameStatePush.value());
		m_pendingGameStatePush.reset();
	}
}

void StateMachine::draw(sf::RenderWindow& win) const
{
	if (!empty())
	{
		m_stack.back()->draw(win);
		m_muteButton.draw(win);
	}
}

void StateMachine::drawPrevState(sf::RenderWindow& win) const
{
	if (m_stack.size() >= 2)
		m_stack[m_stack.size() - 2]->draw(win);
}
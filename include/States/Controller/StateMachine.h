#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Command/ICommand.h"
#include "State.h"
#include <optional>
#include "Button/Button.h"

class StateMachine {
public:
	explicit StateMachine(sf::RenderWindow& win);

	template <typename T, typename... Args>
	void push(Args&&... args);

	void requestPop(size_t times = 1);

	void handleEvent(const sf::Event& e);
	void update(sf::Time dt);
	void draw(sf::RenderWindow& win) const;
	void drawPrevState(sf::RenderWindow& win) const;

	void requestPushGameState(int levelNum) { m_pendingGameStatePush = levelNum; }

	bool empty() const { return m_stack.empty(); }

	sf::RenderWindow& getWindow() { return m_window; }
	Button& getBackButton() { return m_backButton; }

private:
	std::vector<std::unique_ptr<State>> m_stack;
	size_t m_pendingPops = 0;
	std::unique_ptr<ICommand> m_postUpdateCommand = nullptr;
	std::optional<int> m_pendingGameStatePush;
	sf::RenderWindow& m_window;

	Button m_muteButton;
	Button m_backButton;

	void pop();
};

template<typename T, typename ...Args>
inline void StateMachine::push(Args&& ...args)
{
	m_stack.emplace_back(std::make_unique<T>(*this, std::forward<Args>(args)...));
}

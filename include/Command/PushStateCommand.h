#pragma once
#include "ICommand.h"
#include "States/Controller/StateMachine.h"
#include <States/Controller/LevelSelectionState.h>
#include <tuple>

template<typename State, typename... Args>
class PushStateCommand : public ICommand {
public:
	explicit PushStateCommand(StateMachine& machine, Args... args) : m_machine(machine), m_args(std::forward<Args>(args)...) {}
	void execute() override
	{
		std::apply(
			[this](auto&&... args)
			{
				m_machine.push<State>(std::forward<decltype(args)>(args)...);
			},
			m_args
		);
	}

private:
	StateMachine& m_machine;
	std::tuple<Args...> m_args;
};
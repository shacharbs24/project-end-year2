#pragma once
#include "ICommand.h"
#include "States/Controller/StateMachine.h"

class PopStateCommand : public ICommand {
public:
    explicit PopStateCommand(StateMachine& machine, size_t times = 1) : m_machine(machine),m_times(times) {}
    void execute() override {m_machine.requestPop(m_times);}

private:
    StateMachine& m_machine;
	size_t m_times;
};


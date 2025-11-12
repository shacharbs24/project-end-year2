#pragma once
#include "ICommand.h"
#include "States/Controller/StateMachine.h"
#include "States/Controller/GameState.h"
#include "Utiles.h"

class RestartLevelCommand : public ICommand {
public:
	explicit RestartLevelCommand(StateMachine& machine, int level);
	void execute() override;
	
private:
	StateMachine& m_machine;
	int m_level;
};
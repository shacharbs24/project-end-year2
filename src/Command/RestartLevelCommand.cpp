#include "Command/RestartLevelCommand.h"

RestartLevelCommand::RestartLevelCommand(StateMachine& machine, int level) : m_machine(machine), m_level(level)
{}

void RestartLevelCommand::execute()
{
	m_machine.requestPop(2);
	if (levelScriptExists(m_level)) m_machine.requestPushGameState(m_level);
}
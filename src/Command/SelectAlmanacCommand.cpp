#include "Command/SelectAlmanacCommand.h"
#include "States/Help/IHelpScreen.h"

SelectAlmanacCommand::SelectAlmanacCommand(IHelpScreen& help, int i) : m_help(help), m_i(i) {}

void SelectAlmanacCommand::execute() { m_help.select(m_i); }
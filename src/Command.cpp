#include "Command.h"

Command::Command(State * state) : state(state) {}

QuitApplicationCommand::QuitApplicationCommand(State * state) : Command(state) {}

void QuitApplicationCommand::execute() {
	state->setExitFlag(true);
}

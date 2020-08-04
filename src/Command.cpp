#include "Command.h"

Command::Command(State * state) : state(state) {}

NOPCommand::NOPCommand(State * state) : Command(state) {}

void NOPCommand::execute() {
	// Absolutely nothing
}

QuitApplicationCommand::QuitApplicationCommand(State * state) : Command(state) {}

void QuitApplicationCommand::execute() {
	state->setExitFlag(true);
}

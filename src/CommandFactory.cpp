#include "CommandFactory.h"

CommandFactory::CommandFactory(State * state) : state(state) {}

Command * CommandFactory::getCommandFromKey(int key) {
	Command * command;
	switch(key) {
		case 'q':
			command = new QuitApplicationCommand(state);
			break;
		default:
			command = new NOPCommand(state);
			break;
	}

	return command;
}

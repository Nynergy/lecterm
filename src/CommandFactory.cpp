#include "CommandFactory.h"

CommandFactory::CommandFactory(State * state) : state(state) {}

Command * CommandFactory::getCommandFromKey(int key) {
	Command * command;
	switch(key) {
		case 'q':
			command = new QuitApplicationCommand(state);
			break;
		case KEY_RESIZE:
			command = new ResizeWindowCommand(state);
			break;
		case 'h':
			command = new FocusPanelLeftCommand(state);
			break;
		case 'l':
			command = new FocusPanelRightCommand(state);
			break;
		default:
			command = new NOPCommand(state);
			break;
	}

	return command;
}

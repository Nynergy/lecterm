#pragma once

#include "Command.h"

class CommandFactory {
private:
	State * state;

public:
	CommandFactory(State * state);
	Command * getCommandFromKey(int key);
};

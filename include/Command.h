#pragma once

#include "State.h"

class Command {
protected:
	State * state;

	Command(State * state);
public:
	virtual ~Command() {}
	virtual void execute() = 0;
};

class NOPCommand : public Command {
public:
	NOPCommand(State * state);
	void execute() override;
};

class QuitApplicationCommand : public Command {
public:
	QuitApplicationCommand(State * state);
	void execute() override;
};

#pragma once

#include "PanelConstructor.h"
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

class ResizeWindowCommand : public Command {
private:
	PanelConstructor panelConstructor;

public:
	ResizeWindowCommand(State * state);
	void execute() override;
};

class FocusPanelRightCommand : public Command {
private:
	void incrementCurrentPanel();

public:
	FocusPanelRightCommand(State * state);
	void execute() override;
};

class FocusPanelLeftCommand : public Command {
private:
	void decrementCurrentPanel();

public:
	FocusPanelLeftCommand(State * state);
	void execute() override;
};

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

FocusPanelRightCommand::FocusPanelRightCommand(State * state) : Command(state) {}

void FocusPanelRightCommand::execute() {
	incrementCurrentPanel();
}

void FocusPanelRightCommand::incrementCurrentPanel() {
	int currentPanelIndex = state->getCurrentPanelIndex();
	state->setCurrentPanel(++currentPanelIndex);
}

FocusPanelLeftCommand::FocusPanelLeftCommand(State * state) : Command(state) {}

void FocusPanelLeftCommand::execute() {
	decrementCurrentPanel();
}

void FocusPanelLeftCommand::decrementCurrentPanel() {
	int currentPanelIndex = state->getCurrentPanelIndex();
	state->setCurrentPanel(--currentPanelIndex);
}

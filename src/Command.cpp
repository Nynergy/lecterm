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

ResizeWindowCommand::ResizeWindowCommand(State * state) : Command(state) {
	panelConstructor = PanelConstructor();
}

void ResizeWindowCommand::execute() {
	std::vector<Panel *> panels = state->getPanels();
	panelConstructor.resizePanels(panels);
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

ScrollDownCommand::ScrollDownCommand(State * state) : Command(state) {}

void ScrollDownCommand::execute() {
	std::vector<Panel *> panels = state->getPanels();
	int currentPanelIndex = state->getCurrentPanelIndex();
	Panel * currentPanel = panels[currentPanelIndex];

	PanelController * controller = currentPanel->getController();
	controller->scrollDown();
}

ScrollUpCommand::ScrollUpCommand(State * state) : Command(state) {}

void ScrollUpCommand::execute() {
	std::vector<Panel *> panels = state->getPanels();
	int currentPanelIndex = state->getCurrentPanelIndex();
	Panel * currentPanel = panels[currentPanelIndex];

	PanelController * controller = currentPanel->getController();
	controller->scrollUp();
}

SelectItemCommand::SelectItemCommand(State * state) : Command(state) {}

void SelectItemCommand::execute() {
	std::vector<Panel *> panels = state->getPanels();
	int currentPanelIndex = state->getCurrentPanelIndex();
	Panel * currentPanel = panels[currentPanelIndex];

	PanelController * controller = currentPanel->getController();
	controller->selectItem();
}

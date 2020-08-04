#include "State.h"

State::State() : exitFlag(false) {}

State::~State() {
	for(auto panel : panels) {
		delete panel;
	}
}

void State::addPanel(Panel * panel) {
	panels.push_back(panel);
}

std::vector<Panel *> State::getPanels() {
	return panels;
}

void State::setExitFlag(bool flag) {
	exitFlag = flag;
}

bool State::userHasQuit() {
	return exitFlag;
}

bool State::userHasNotQuit() {
	return !userHasQuit();
}

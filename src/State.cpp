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

void State::setCurrentPanel(int panelIndex) {
	panelIndex = wrapIndex(panelIndex);
	currentPanel = panelIndex;
}

int State::wrapIndex(int index) {
	if(index > (int)panels.size() - 1) {
		return 0;
	}

	if(index < 0) {
		return panels.size() - 1;
	}

	return index;
}

Panel * State::getCurrentPanel() {
	return panels[currentPanel];
}

int State::getCurrentPanelIndex() {
	return currentPanel;
}

bool State::panelIsFocused(Panel * panel) {
	return panel == panels[currentPanel];
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

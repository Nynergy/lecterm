#include "State.h"

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

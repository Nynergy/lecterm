#pragma once

#include <vector>

#include "Panel.h"

class State {
private:
	std::vector<Panel *> panels;

public:
	~State();
	void addPanel(Panel * panel);
	std::vector<Panel *> getPanels();
};

#pragma once

#include <vector>

#include "Panel.h"

class State {
private:
	std::vector<Panel *> panels;
	bool exitFlag;

public:
	State();
	~State();
	void addPanel(Panel * panel);
	std::vector<Panel *> getPanels();
	void setExitFlag(bool flag);
	bool userHasQuit();
	bool userHasNotQuit();
};

#pragma once

#include <vector>

#include "Panel.h"

class State {
private:
	std::vector<Panel *> panels;
	std::vector<Panel *>::iterator currentPanel;
	bool exitFlag;

public:
	State();
	~State();
	void addPanel(Panel * panel);
	std::vector<Panel *> getPanels();
	void setCurrentPanel(std::vector<Panel *>::iterator panel);
	bool panelIsFocused(Panel * panel);
	void setExitFlag(bool flag);
	bool userHasQuit();
	bool userHasNotQuit();
};

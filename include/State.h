#pragma once

#include <vector>

#include "Panel.h"

class State {
private:
	std::vector<Panel *> panels;
	int currentPanel;
	bool exitFlag;

	int wrapIndex(int index);

public:
	State();
	~State();
	void addPanel(Panel * panel);
	std::vector<Panel *> getPanels();
	void setCurrentPanel(int panelIndex);
	Panel * getCurrentPanel();
	int getCurrentPanelIndex();
	bool panelIsFocused(Panel * panel);
	void setExitFlag(bool flag);
	bool userHasQuit();
	bool userHasNotQuit();
};

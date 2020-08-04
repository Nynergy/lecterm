#pragma once

#include <vector>

#include "PanelConstructor.h"

class Engine {
private:
	PanelConstructor panelConstructor;
	std::vector<Panel *> panels;

	void setupCursesEnvironment();
	void initializeColorPairs();
	void teardownCursesEnvironment();
	void constructPanels();
	void renderPanels();
	void handleInput(int key);

public:
	Engine();
	~Engine();
	void init();
	void run();
};

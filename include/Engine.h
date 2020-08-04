#pragma once

#include "PanelConstructor.h"
#include "State.h"

class Engine {
private:
	State * state;

	PanelConstructor panelConstructor;

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

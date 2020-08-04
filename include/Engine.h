#pragma once

#include "PanelConstructor.h"

class Engine {
private:
	PanelConstructor panelConstructor;

	void setupCursesEnvironment();
	void initializeColorPairs();
	void teardownCursesEnvironment();

public:
	Engine();
	~Engine();
	void drawingTest();
};

#pragma once

#include "Panel.h"

class Engine {
private:
	void setupCursesEnvironment();
	void initializeColorPairs();
	void teardownCursesEnvironment();

public:
	Engine();
	~Engine();
	void drawingTest();
};

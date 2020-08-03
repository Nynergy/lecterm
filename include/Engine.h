#pragma once

#include "CursesUtil.h"

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

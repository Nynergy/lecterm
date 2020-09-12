#pragma once

#include "CommandFactory.h"
#include "FileProcessor.h" // FIXME: Remove after testing complete
#include "PanelConstructor.h"

class Engine {
private:
	State * state;

	CommandFactory * commandFactory;
	PanelConstructor * panelConstructor;

	void setupCursesEnvironment();
	void initializeColorPairs();
	bool transparencyIsSet();
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

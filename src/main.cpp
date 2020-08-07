#include <iostream>

#include "Engine.h"

int main() {
	Config::getInstance().readFromConfigFile();

	Engine * engine = new Engine();
	engine->init();
	engine->run();

	delete engine;
}

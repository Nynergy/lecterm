#include <iostream>

#include "Engine.h"

int main() {
	Engine * engine = new Engine();

	engine->drawingTest();

	int ch = getch();

	delete engine;
}

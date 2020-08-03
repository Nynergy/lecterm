#include "Engine.h"

Engine::Engine() {
	setupCursesEnvironment();
}

Engine::~Engine() {
	teardownCursesEnvironment();
}

void Engine::setupCursesEnvironment() {
	// Initialize curses environment
	initscr();		// Begin curses mode
	cbreak();		// Disable line buffering
	keypad(stdscr, TRUE);	// Enable extra keys
	noecho();		// Disable echoing keys to console
	start_color();		// Enable color mode
	curs_set(0);		// Set cursor to be invisible

	initializeColorPairs();
}

void Engine::initializeColorPairs() {
	use_default_colors();	// Enable transparency

	init_pair(0, COLOR_BLACK, -1);
	init_pair(1, COLOR_RED, -1);
	init_pair(2, COLOR_GREEN, -1);
	init_pair(3, COLOR_YELLOW, -1);
	init_pair(4, COLOR_BLUE, -1);
	init_pair(5, COLOR_MAGENTA, -1);
	init_pair(6, COLOR_CYAN, -1);
	init_pair(7, COLOR_WHITE, -1);
}

void Engine::teardownCursesEnvironment() {
	endwin();	// Destroy stdscr
}

void Engine::drawingTest() {
	Panel myPanel = Panel(Point(10, 10), 10, 20);
	myPanel.drawToScreen();
}

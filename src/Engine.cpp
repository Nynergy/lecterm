#include "Engine.h"

Engine::Engine() {
	setupCursesEnvironment();

	state = new State();
	panelConstructor = PanelConstructor();
}

Engine::~Engine() {
	delete state;

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

void Engine::init() {
	constructPanels();
}

void Engine::constructPanels() {
	state->addPanel(panelConstructor.getNewNotebookPanel());
	state->addPanel(panelConstructor.getNewNoteListPanel());
	state->addPanel(panelConstructor.getNewNotePanel());
}

void Engine::run() {
	int key;
	while(state->userHasNotQuit()) {
		renderPanels();
		key = getch();
		handleInput(key);
	}
}

void Engine::renderPanels() {
	for(auto panel : state->getPanels()) {
		panel->drawToScreen();
	}
}

void Engine::handleInput(int key) {
	// TODO: Convert keys to the appropriate Command
	if(key == 'q') {
		Command * command = new QuitApplicationCommand(state);
		command->execute();
		delete command;
	}
}

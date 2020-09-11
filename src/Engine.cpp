#include "Engine.h"

Engine::Engine() {
	setupCursesEnvironment();

	state = new State();
	commandFactory = new CommandFactory(state);
	panelConstructor = new PanelConstructor();
}

Engine::~Engine() {
	delete state;
	delete commandFactory;
	delete panelConstructor;

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
	timeout(50);		// Make getch a non-blocking call

	initializeColorPairs();
}

void Engine::initializeColorPairs() {
	int backgroundColor = COLOR_BLACK;
	if(transparencyIsSet()) {
		use_default_colors();
		backgroundColor = -1;	// -1 is ncurses transparent color
	}

	init_pair(0, COLOR_BLACK, backgroundColor);
	init_pair(1, COLOR_RED, backgroundColor);
	init_pair(2, COLOR_GREEN, backgroundColor);
	init_pair(3, COLOR_YELLOW, backgroundColor);
	init_pair(4, COLOR_BLUE, backgroundColor);
	init_pair(5, COLOR_MAGENTA, backgroundColor);
	init_pair(6, COLOR_CYAN, backgroundColor);
	init_pair(7, COLOR_WHITE, backgroundColor);
}

bool Engine::transparencyIsSet() {
	Config & config = Config::getInstance();
	std::string transparencyValue = config.getValueFromKey("Transparency");
	if(transparencyValue == "true") return true;
	else return false;
}

void Engine::teardownCursesEnvironment() {
	endwin();	// Destroy stdscr
}

void Engine::init() {
	constructPanels();
}

void Engine::constructPanels() {
	state->addPanel(panelConstructor->getNewNotebookPanel());
	state->addPanel(panelConstructor->getNewNoteListPanel());
	state->addPanel(panelConstructor->getNewNotePanel());

	state->setCurrentPanel(0);
}

void Engine::run() {
	int key;
	while(state->userHasNotQuit()) {
		key = getch();
		renderPanels();
		handleInput(key);
	}
}

void Engine::renderPanels() {
	for(auto panel : state->getPanels()) {
		if(state->panelIsFocused(panel)) {
			panel->drawFocusedToScreen();
		} else {
			panel->drawToScreen();
		}
	}

	refresh();
}

void Engine::handleInput(int key) {
	Command * command = commandFactory->getCommandFromKey(key);
	command->execute();
	delete command;
}

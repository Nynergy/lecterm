#include "PanelConstructor.h"

static const float NOTEBOOK_PANEL_RATIO = 0.2;
static const float NOTE_LIST_PANEL_RATIO = 0.2;
static const float NOTE_PANEL_RATIO = 0.6;

PanelConstructor::PanelConstructor() {}

PanelConstructor::~PanelConstructor() {}

Panel * PanelConstructor::getNewNotebookPanel() {
	Point upperLeftCorner = Point(0, 0);
	int lines = CursesUtil::maxLines();
	int columns = calculateColumnsByRatio(NOTEBOOK_PANEL_RATIO);

	Panel * notebooks = new Panel(upperLeftCorner, lines, columns);
	notebooks->setTitle("Notebooks");

	return notebooks;
}

Panel * PanelConstructor::getNewNoteListPanel() {
	int offset = calculateColumnsByRatio(NOTEBOOK_PANEL_RATIO);
	Point upperLeftCorner = Point(offset, 0);
	int lines = CursesUtil::maxLines();
	int columns = calculateColumnsByRatio(NOTE_LIST_PANEL_RATIO);

	Panel * noteList = new Panel(upperLeftCorner, lines, columns);
	noteList->setTitle("Note List");

	return noteList;
}

Panel * PanelConstructor::getNewNotePanel() {
	int offsetOne = calculateColumnsByRatio(NOTEBOOK_PANEL_RATIO);
	int offsetTwo = calculateColumnsByRatio(NOTE_LIST_PANEL_RATIO);
	int offset = offsetOne + offsetTwo;
	Point upperLeftCorner = Point(offset, 0);
	int lines = CursesUtil::maxLines();
	int columns = calculateColumnsByOffset(offset);

	Panel * note = new Panel(upperLeftCorner, lines, columns);
	note->setTitle("Note");

	return note;
}

int PanelConstructor::calculateColumnsByRatio(float ratio) {
	int columns = floor(ratio * CursesUtil::maxColumns());

	return columns;
}

int PanelConstructor::calculateColumnsByOffset(int offset) {
	int columns = CursesUtil::maxColumns() - offset;

	return columns;
}

// First three panels should always be the same
void PanelConstructor::resizePanels(std::vector<Panel *> panels) {
	Panel * notebookPanel = panels[0];
	Panel * noteListPanel = panels[1];
	Panel * notePanel = panels[2];

	resizeNotebookPanel(notebookPanel);
	resizeNoteListPanel(noteListPanel);
	resizeNotePanel(notePanel);

	for(auto panel : panels) {
		panel->replaceWindow();
	}
}

void PanelConstructor::resizeNotebookPanel(Panel * panel) {
	Point upperLeftCorner = Point(0, 0);
	int lines = CursesUtil::maxLines();
	int columns = calculateColumnsByRatio(NOTEBOOK_PANEL_RATIO);

	panel->setUpperLeftCorner(upperLeftCorner);
	panel->setLines(lines);
	panel->setColumns(columns);
}

void PanelConstructor::resizeNoteListPanel(Panel * panel) {
	int offset = calculateColumnsByRatio(NOTEBOOK_PANEL_RATIO);
	Point upperLeftCorner = Point(offset, 0);
	int lines = CursesUtil::maxLines();
	int columns = calculateColumnsByRatio(NOTE_LIST_PANEL_RATIO);

	panel->setUpperLeftCorner(upperLeftCorner);
	panel->setLines(lines);
	panel->setColumns(columns);
}

void PanelConstructor::resizeNotePanel(Panel * panel) {
	int offsetOne = calculateColumnsByRatio(NOTEBOOK_PANEL_RATIO);
	int offsetTwo = calculateColumnsByRatio(NOTE_LIST_PANEL_RATIO);
	int offset = offsetOne + offsetTwo;
	Point upperLeftCorner = Point(offset, 0);
	int lines = CursesUtil::maxLines();
	int columns = calculateColumnsByOffset(offset);

	panel->setUpperLeftCorner(upperLeftCorner);
	panel->setLines(lines);
	panel->setColumns(columns);
}

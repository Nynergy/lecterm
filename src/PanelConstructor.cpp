#include "PanelConstructor.h"

static const float NOTEBOOK_PANEL_RATIO = 0.2;
static const float NOTE_LIST_PANEL_RATIO = 0.2;
static const float NOTE_PANEL_RATIO = 0.6;

PanelConstructor::PanelConstructor() {}

PanelConstructor::~PanelConstructor() {}

Panel * PanelConstructor::getNewNotebookPanel() {
	PanelDimensions panelDimensions = getNotebookPanelDimensions();

	Panel * notebooks = new ListPanel(panelDimensions);
	notebooks->setTitle("Notebooks");

	return notebooks;
}

PanelDimensions PanelConstructor::getNotebookPanelDimensions() {
	Point upperLeftCorner = Point(0, 0);
	int lines = CursesUtil::maxLines();
	int columns = calculateColumnsByRatio(NOTEBOOK_PANEL_RATIO);

	return PanelDimensions(upperLeftCorner, lines, columns);
}

Panel * PanelConstructor::getNewNoteListPanel() {
	PanelDimensions panelDimensions = getNoteListPanelDimensions();

	Panel * noteList = new ListPanel(panelDimensions);
	noteList->setTitle("Note List");

	return noteList;
}

PanelDimensions PanelConstructor::getNoteListPanelDimensions() {
	int offset = calculateColumnsByRatio(NOTEBOOK_PANEL_RATIO);
	Point upperLeftCorner = Point(offset, 0);
	int lines = CursesUtil::maxLines();
	int columns = calculateColumnsByRatio(NOTE_LIST_PANEL_RATIO);

	return PanelDimensions(upperLeftCorner, lines, columns);
}

Panel * PanelConstructor::getNewNotePanel() {
	PanelDimensions panelDimensions = getNotePanelDimensions();

	Panel * note = new TextPanel(panelDimensions);
	note->setTitle("Note");

	return note;
}

PanelDimensions PanelConstructor::getNotePanelDimensions() {
	int offsetOne = calculateColumnsByRatio(NOTEBOOK_PANEL_RATIO);
	int offsetTwo = calculateColumnsByRatio(NOTE_LIST_PANEL_RATIO);
	int offset = offsetOne + offsetTwo;
	Point upperLeftCorner = Point(offset, 0);
	int lines = CursesUtil::maxLines();
	int columns = calculateColumnsByOffset(offset);

	return PanelDimensions(upperLeftCorner, lines, columns);
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
	PanelDimensions panelDimensions = getNotebookPanelDimensions();
	setPanelDimensions(panel, panelDimensions);
}

void PanelConstructor::resizeNoteListPanel(Panel * panel) {
	PanelDimensions panelDimensions = getNoteListPanelDimensions();
	setPanelDimensions(panel, panelDimensions);
}

void PanelConstructor::resizeNotePanel(Panel * panel) {
	PanelDimensions panelDimensions = getNotePanelDimensions();
	setPanelDimensions(panel, panelDimensions);
}

void PanelConstructor::setPanelDimensions(Panel * panel, PanelDimensions panelDimensions) {
	panel->setUpperLeftCorner(panelDimensions.upperLeft);
	panel->setLines(panelDimensions.lines);
	panel->setColumns(panelDimensions.columns);
}

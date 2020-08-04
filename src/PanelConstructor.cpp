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

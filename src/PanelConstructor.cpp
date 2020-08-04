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

	return new Panel(upperLeftCorner, lines, columns);
}

Panel * PanelConstructor::getNewNoteListPanel() {
	int offset = calculateColumnsByRatio(NOTEBOOK_PANEL_RATIO);
	Point upperLeftCorner = Point(offset + 1, 0);
	int lines = CursesUtil::maxLines();
	int columns = calculateColumnsByRatio(NOTE_LIST_PANEL_RATIO);

	return new Panel(upperLeftCorner, lines, columns);
}

Panel * PanelConstructor::getNewNotePanel() {
	int offsetOne = calculateColumnsByRatio(NOTEBOOK_PANEL_RATIO);
	int offsetTwo = calculateColumnsByRatio(NOTE_LIST_PANEL_RATIO);
	int offset = offsetOne + offsetTwo;
	Point upperLeftCorner = Point(offset + 1, 0);
	int lines = CursesUtil::maxLines();
	int columns = calculateColumnsByRatio(NOTE_PANEL_RATIO);

	return new Panel(upperLeftCorner, lines, columns);
}

int PanelConstructor::calculateColumnsByRatio(float ratio) {
	int columns = floor(ratio * CursesUtil::maxColumns());

	return columns;
}

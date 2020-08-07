#include "Panel.h"

Panel::Panel(PanelDimensions panelDimensions) {
	title = "";
	upperLeftCorner = panelDimensions.upperLeft;
	lines = panelDimensions.lines;
	columns = panelDimensions.columns;

	setupWindow();
}

Panel::~Panel() {
	teardownWindow();
}

void Panel::setupWindow() {
	window = newwin(lines, columns, upperLeftCorner.y, upperLeftCorner.x);
}

void Panel::teardownWindow() {
	delwin(window);
}

void Panel::drawToScreen() {
	drawBorder();
	drawTitle();
	refreshWindow();
}

void Panel::drawFocusedToScreen() {
	drawFocusedBorder();
	drawTitle();
	refreshWindow();
}

void Panel::drawFocusedBorder() {
	CursesUtil::setWindowAttributes(window, CursesUtil::getColor("red"));
	drawBorder();
	CursesUtil::unsetWindowAttributes(window, CursesUtil::getColor("red"));
}

void Panel::drawBorder() {
	BoxCorners corners = getPanelCorners();
	CursesUtil::drawBoxAtCorners(window, corners);
}

BoxCorners Panel::getPanelCorners() {
	Point upperLeft = Point(0, 0);
	Point upperRight = Point(upperLeft.x + (columns - 1), upperLeft.y);
	Point lowerLeft = Point(upperLeft.x, upperLeft.y + (lines - 1));
	Point lowerRight = Point(upperRight.x, lowerLeft.y);

	return BoxCorners(upperLeft, upperRight, lowerLeft, lowerRight);
}

void Panel::drawTitle() {
	Point titlePoint = calculateTitlePoint();
	CursesUtil::drawStringAtPoint(window, title, titlePoint);
}

Point Panel::calculateTitlePoint() {
	int panelHalfWidth = columns / 2;
	int titleHalfWidth = title.length() / 2;
	int x = panelHalfWidth - titleHalfWidth;

	return Point(x, 0);
}

void Panel::refreshWindow() {
	wrefresh(window);
}

void Panel::setTitle(std::string newTitle) {
	title = newTitle;
}

void Panel::setUpperLeftCorner(Point upperLeft) {
	upperLeftCorner = upperLeft;
}

void Panel::setLines(int newLines) {
	lines = newLines;
}

void Panel::setColumns(int newColumns) {
	columns = newColumns;
}

void Panel::replaceWindow() {
	delwin(window);
	window = newwin(lines, columns, upperLeftCorner.y, upperLeftCorner.x);
}

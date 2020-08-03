#include "Panel.h"

Panel::Panel(Point upperLeftCorner, int lines, int columns) :
	upperLeftCorner(upperLeftCorner), lines(lines), columns(columns) {
	
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
	refreshWindow();
}

void Panel::drawBorder() {
	BoxCorners corners = getPanelCorners();
	CursesUtil::drawBoxAtCorners(corners);
}

BoxCorners Panel::getPanelCorners() {
	Point upperLeft = upperLeftCorner;
	Point upperRight = Point(upperLeftCorner.x + (columns - 1), upperLeftCorner.y);
	Point lowerLeft = Point(upperLeftCorner.x, upperLeftCorner.y + (lines - 1));
	Point lowerRight = Point(upperLeftCorner.x + (columns - 1), upperLeftCorner.y + (lines - 1));

	return BoxCorners(upperLeft, upperRight, lowerLeft, lowerRight);
}

void Panel::refreshWindow() {
	wrefresh(window);
}

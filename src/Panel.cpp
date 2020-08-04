#include "Panel.h"

Panel::Panel(Point upperLeftCorner, int lines, int columns) :
	title(""), upperLeftCorner(upperLeftCorner),
	lines(lines), columns(columns) {
	
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

void Panel::drawTitle() {
	Point titlePoint = calculateTitlePoint();
	CursesUtil::drawStringAtPoint(title, titlePoint);
}

Point Panel::calculateTitlePoint() {
	int panelHalfWidth = columns / 2;
	int titleHalfWidth = title.length() / 2;
	int offset = panelHalfWidth - titleHalfWidth;
	int x = upperLeftCorner.x + offset;

	return Point(x, upperLeftCorner.y);
}

void Panel::refreshWindow() {
	wrefresh(window);
}

void Panel::setTitle(std::string newTitle) {
	title = newTitle;
}

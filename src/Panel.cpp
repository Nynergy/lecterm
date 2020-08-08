#include "Panel.h"

Panel::Panel(PanelDimensions panelDimensions) {
	title = "";
	upperLeftCorner = panelDimensions.upperLeft;
	lines = panelDimensions.lines;
	columns = panelDimensions.columns;

	setupWindow();
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
	Config & config = Config::getInstance();
	std::string borderColorString = config.getValueFromKey("FocusColor");
	int borderColor = CursesUtil::getColor(borderColorString);
	CursesUtil::setWindowAttributes(window, borderColor);
	drawBorder();
	CursesUtil::unsetWindowAttributes(window, borderColor);
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

std::string Panel::truncateStringByLength(std::string str, int length) {
	if(length >= (int)str.length()) {
		return str;
	}

	std::string truncated = str.substr(0, length);

	return truncated;
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

ListPanel::ListPanel(PanelDimensions panelDimensions) : Panel(panelDimensions) {}

ListPanel::~ListPanel() {
	teardownWindow();
}

void ListPanel::drawToScreen() {
	drawBorder();
	drawTitle();
	drawItems();
	refreshWindow();
}

void ListPanel::drawFocusedToScreen() {
	drawFocusedBorder();
	drawTitle();
	drawItems();
	refreshWindow();
}

void ListPanel::drawItems() {
	int itemCounter = 0;
	for(std::string item : content.getItems()) {
		Point itemPoint = Point(1, ++itemCounter);
		std::string text = truncateStringByLength(item, columns - 2);
		CursesUtil::drawStringAtPoint(window, text, itemPoint);
	}
}

ContentPanel::ContentPanel(PanelDimensions panelDimensions) : Panel(panelDimensions) {}

ContentPanel::~ContentPanel() {
	teardownWindow();
}

void ContentPanel::drawToScreen() {
	drawBorder();
	drawTitle();
	refreshWindow();
}

void ContentPanel::drawFocusedToScreen() {
	drawFocusedBorder();
	drawTitle();
	refreshWindow();
}

PanelContent::PanelContent() {}

std::vector<std::string> PanelContent::getItems() {
	return items;
}

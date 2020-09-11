#include "Panel.h"

static const int ITEM_START_COLUMN = 1;
static const int BORDER_OFFSET = 2;
static const int ITEM_INDEX_OFFSET = 1;

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

PanelController * Panel::getController() {
	return controller;
}

PanelContent * Panel::getContent() {
	return content;
}

void Panel::replaceWindow() {
	delwin(window);
	window = newwin(lines, columns, upperLeftCorner.y, upperLeftCorner.x);
}

ListPanel::ListPanel(PanelDimensions panelDimensions) : Panel(panelDimensions) {
	controller = new ListPanelController(this);
	content = new ListPanelContent();
}

ListPanel::~ListPanel() {
	delete controller;
	delete content;

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
	for(std::string item : content->getItems()) {
		drawItem(item, ++itemCounter);
	}
}

void ListPanel::drawItem(std::string item, int itemCounter) {
	Point itemPoint = Point(ITEM_START_COLUMN, itemCounter);
	std::string text = truncateStringByLength(item, columns - BORDER_OFFSET);

	int attr = getAttributesByIndex(itemCounter - ITEM_INDEX_OFFSET);

	CursesUtil::setWindowAttributes(window, attr);
	CursesUtil::drawStringAtPoint(window, text, itemPoint);
	CursesUtil::unsetWindowAttributes(window, attr);
}

int ListPanel::getAttributesByIndex(int index) {
	int attr = A_NORMAL;
	if(itemIsHovered(index)) {
		attr |= A_REVERSE;
	}
	if(itemIsSelected(index)) {
		Config & config = Config::getInstance();
		std::string itemColorString = config.getValueFromKey("SelectionColor");
		int itemColor = CursesUtil::getColor(itemColorString);
		attr |= itemColor;
	}

	return attr;
}

bool ListPanel::itemIsHovered(int itemIndex) {
	ListPanelContent * listContent = (ListPanelContent *)content;
	return listContent->getHoverIndex() == itemIndex;
}

bool ListPanel::itemIsSelected(int itemIndex) {
	ListPanelContent * listContent = (ListPanelContent *)content;
	return listContent->getSelectionIndex() == itemIndex;
}

TextPanel::TextPanel(PanelDimensions panelDimensions) : Panel(panelDimensions) {
	controller = new TextPanelController(this);
	content = new TextPanelContent();
}

TextPanel::~TextPanel() {
	delete controller;
	delete content;

	teardownWindow();
}

void TextPanel::drawToScreen() {
	drawBorder();
	drawTitle();
	drawItems();
	refreshWindow();
}

void TextPanel::drawFocusedToScreen() {
	drawFocusedBorder();
	drawTitle();
	drawItems();
	refreshWindow();
}

void TextPanel::drawItems() {
	int itemCounter = 0;
	for(std::string item : content->getItems()) {
		drawItem(item, ++itemCounter);
	}
}

void TextPanel::drawItem(std::string item, int itemCounter) {
	Point itemPoint = Point(ITEM_START_COLUMN, itemCounter);
	// FIXME In the future, TextPanelContent will wrap text lines to fit
	// the panel's window, so there will be no need to truncate lines
	std::string text = truncateStringByLength(item, columns - BORDER_OFFSET);
	CursesUtil::drawStringAtPoint(window, text, itemPoint);
}

PanelContent::PanelContent() {
	addItem("Item One");
	addItem("Item Two");
	addItem("Item Three");
	addItem("Item Four");
	addItem("Item Five");
}

void PanelContent::addItem(std::string item) {
	items.push_back(item);
}

std::vector<std::string> PanelContent::getItems() {
	return items;
}

ListPanelContent::ListPanelContent() : PanelContent(), hoverIndex(0), selectionIndex(-1) {}

int ListPanelContent::getHoverIndex() {
	return hoverIndex;
}

void ListPanelContent::incrementHoverIndex() {
	hoverIndex = (hoverIndex + 1) % items.size();
}

void ListPanelContent::decrementHoverIndex() {
	hoverIndex = hoverIndex == 0 ? items.size() - 1 : hoverIndex - 1;
}

int ListPanelContent::getSelectionIndex() {
	return selectionIndex;
}

void ListPanelContent::setSelectionIndex(int index) {
	selectionIndex = index;
}

TextPanelContent::TextPanelContent() : PanelContent() {}

PanelController::PanelController(Panel * parent) : parent(parent) {}

ListPanelController::ListPanelController(Panel * parent) : PanelController(parent) {}

void ListPanelController::scrollDown() {
	ListPanelContent * content = (ListPanelContent *)parent->getContent();
	content->incrementHoverIndex();
}

void ListPanelController::scrollUp() {
	ListPanelContent * content = (ListPanelContent *)parent->getContent();
	content->decrementHoverIndex();
}

void ListPanelController::selectItem() {
	ListPanelContent * content = (ListPanelContent *)parent->getContent();
	int hoverIndex = content->getHoverIndex();
	content->setSelectionIndex(hoverIndex);
}

TextPanelController::TextPanelController(Panel * parent) : PanelController(parent) {}

void TextPanelController::scrollDown() {
	// TODO: Scroll text
	return;
}

void TextPanelController::scrollUp() {
	// TODO: Scroll text
	return;
}

void TextPanelController::selectItem() {
	// NOTE: The text panel has nothing to 'select'
	return;
}

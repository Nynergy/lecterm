#include "Panel.h"

static const int ITEM_START_COLUMN = 1;
static const int BORDER_OFFSET = 2;
static const int ITEM_INDEX_OFFSET = 1;

int getColorFromString(std::string color) {
	Config & config = Config::getInstance();
	std::string colorString = config.getValueFromKey(color);
	int colorNum = CursesUtil::getColor(colorString);

	return colorNum;
}

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
	int borderColor = getColorFromString("FocusColor");
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

void Panel::clearScreen() {
	for(int y = 1; y < lines - 1; y++) {
		for(int x = 1; x < columns - 1; x++) {
			Point p(x, y);
			CursesUtil::drawCharAtPoint(window, ' ', p);
		}
	}
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
		int itemColor = getColorFromString("SelectionColor");
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
	clearScreen();
	std::vector<std::string> wrappedLines = getWrappedLines();

	// Manipulate contentOffset
	TextPanelContent * textContent = (TextPanelContent *)content;
	int contentOffset = textContent->getContentOffset();
	if(contentSmallerThanWindow(wrappedLines.size()) || (contentOffset < 0)) {
		contentOffset = 0;
		textContent->setContentOffset(contentOffset);
	} else if(endOfContentReached(contentOffset, wrappedLines.size())) {
		contentOffset = wrappedLines.size() - (lines - BORDER_OFFSET);
		textContent->setContentOffset(contentOffset);
	}

	// Draw lines based on offset
	int offsetCounter = 0;
	int lineCounter = 0;
	for(std::string line : wrappedLines) {
		if(offsetCounter < contentOffset) {
			// Effectively skip this line
			offsetCounter++;
			continue;
		}

		if(lineCounter < lines - BORDER_OFFSET) {
			drawItem(line, ++lineCounter);
		}
	}
}

std::vector<std::string> TextPanel::getWrappedLines() {
	int width = columns - BORDER_OFFSET;
	std::vector<std::string> items = content->getItems();
	std::vector<std::string> wrapped = WordWrapper::getWrappedLinesFromWidth(items, width);

	return wrapped;
}

bool TextPanel::contentSmallerThanWindow(int contentSize) {
	return contentSize - BORDER_OFFSET < lines;
}

bool TextPanel::endOfContentReached(int contentOffset, int contentSize) {
	return contentOffset > contentSize - (lines - BORDER_OFFSET);
}

void TextPanel::drawItem(std::string item, int itemCounter) {
	Point itemPoint = Point(ITEM_START_COLUMN, itemCounter);
	CursesUtil::drawStringAtPoint(window, item, itemPoint);
}

PanelContent::PanelContent() {
	// FIXME: Remove once directory contents can be piped to Panels
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

void PanelContent::setItems(std::vector<std::string> newItems) {
	items = newItems;
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

TextPanelContent::TextPanelContent() : PanelContent(), contentOffset(0) {}

int TextPanelContent::getContentOffset() {
	return contentOffset;
}

void TextPanelContent::setContentOffset(int offset) {
	contentOffset = offset;
}

void TextPanelContent::incrementContentOffset() {
	contentOffset++;
}

void TextPanelContent::decrementContentOffset() {
	contentOffset--;
}

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
	TextPanelContent * content = (TextPanelContent *)parent->getContent();
	content->incrementContentOffset();
	return;
}

void TextPanelController::scrollUp() {
	TextPanelContent * content = (TextPanelContent *)parent->getContent();
	content->decrementContentOffset();
	return;
}

void TextPanelController::selectItem() {
	// NOTE: The text panel has nothing to 'select'
	return;
}

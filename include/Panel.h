#pragma once

#include <vector>

#include "Config.h"
#include "CursesUtil.h"
#include "WordWrapper.h"

class PanelController;

int getColorFromString(std::string color);

class PanelContent {
protected:
	std::vector<std::string> items;

public:
	PanelContent();
	void addItem(std::string item);
	std::vector<std::string> getItems();
	void setItems(std::vector<std::string> newItems);
};

class ListPanelContent : public PanelContent {
private:
	int hoverIndex;
	int selectionIndex;

public:
	ListPanelContent();
	int getHoverIndex();
	void incrementHoverIndex();
	void decrementHoverIndex();
	int getSelectionIndex();
	void setSelectionIndex(int index);
};

class TextPanelContent : public PanelContent {
private:
	int contentOffset;

public:
	TextPanelContent();
	int getContentOffset();
	void setContentOffset(int offset);
	void incrementContentOffset();
	void decrementContentOffset();
};

class Panel {
protected:
	WINDOW * window;
	std::string title;
	Point upperLeftCorner;
	int lines, columns;
	PanelController * controller;
	PanelContent * content;

	void setupWindow();
	void teardownWindow();
	void drawFocusedBorder();
	void drawBorder();
	void drawTitle();
	Point calculateTitlePoint();
	std::string truncateStringByLength(std::string str, int length);
	void refreshWindow();
	BoxCorners getPanelCorners();
	void clearScreen();

public:
	Panel(PanelDimensions panelDimensions);
	virtual ~Panel() {}
	virtual void drawToScreen();
	virtual void drawFocusedToScreen();
	void setTitle(std::string newTitle);
	void setUpperLeftCorner(Point upperLeft);
	void setLines(int newLines);
	void setColumns(int newColumns);
	PanelController * getController();
	PanelContent * getContent();
	void replaceWindow();
};

class ListPanel : public Panel {
private:
	void drawItems();
	void drawItem(std::string item, int itemCounter);
	int getAttributesByIndex(int index);
	bool itemIsHovered(int itemIndex);
	bool itemIsSelected(int itemIndex);

public:
	ListPanel(PanelDimensions panelDimensions);
	~ListPanel();
	void drawToScreen() override;
	void drawFocusedToScreen() override;
};

class TextPanel : public Panel {
private:
	void drawItems();
	std::vector<std::string> getWrappedLines();
	bool contentSmallerThanWindow(int contentSize);
	bool endOfContentReached(int contentOffset, int contentSize);
	void drawItem(std::string item, int itemCounter);

public:
	TextPanel(PanelDimensions panelDimensions);
	~TextPanel();
	void drawToScreen() override;
	void drawFocusedToScreen() override;
};

class PanelController {
protected:
	Panel * parent;

public:
	PanelController(Panel * parent);
	virtual ~PanelController() {}

	virtual void scrollDown() = 0;
	virtual void scrollUp() = 0;
	virtual void selectItem() = 0;
};

class ListPanelController : public PanelController {
public:
	ListPanelController(Panel * parent);
	void scrollDown() override;
	void scrollUp() override;
	void selectItem() override;
};

class TextPanelController : public PanelController {
public:
	TextPanelController(Panel * parent);
	void scrollDown() override;
	void scrollUp() override;
	void selectItem() override;
};

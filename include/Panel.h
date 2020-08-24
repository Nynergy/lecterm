#pragma once

#include <vector>

#include "Config.h"
#include "CursesUtil.h"

class PanelController;

class PanelContent {
protected:
	std::vector<std::string> items;

public:
	PanelContent();
	void addItem(std::string item);
	std::vector<std::string> getItems();
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
};

class TextPanelContent : public PanelContent {
public:
	TextPanelContent();
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
	bool itemIsHovered(int itemIndex);

public:
	ListPanel(PanelDimensions panelDimensions);
	~ListPanel();
	void drawToScreen() override;
	void drawFocusedToScreen() override;
};

class TextPanel : public Panel {
private:
	void drawItems();
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
};

class ListPanelController : public PanelController {
public:
	ListPanelController(Panel * parent);
	void scrollDown() override;
	void scrollUp() override;
};

class TextPanelController : public PanelController {
public:
	TextPanelController(Panel * parent);
	void scrollDown() override;
	void scrollUp() override;
};

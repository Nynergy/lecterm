#pragma once

#include <vector>

#include "Config.h"
#include "CursesUtil.h"

class PanelContent {
private:
	std::vector<std::string> items;

public:
	PanelContent();
	std::vector<std::string> getItems();
};

class Panel {
protected:
	WINDOW * window;
	std::string title;
	Point upperLeftCorner;
	int lines, columns;

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
	void replaceWindow();
};

class ListPanel : public Panel {
private:
	PanelContent content;

	void drawItems();

public:
	ListPanel(PanelDimensions panelDimensions);
	~ListPanel();
	void drawToScreen() override;
	void drawFocusedToScreen() override;
};

class ContentPanel : public Panel {
public:
	ContentPanel(PanelDimensions panelDimensions);
	~ContentPanel();
	void drawToScreen() override;
	void drawFocusedToScreen() override;
};

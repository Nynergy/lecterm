#pragma once

#include "CursesUtil.h"

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
	void refreshWindow();
	BoxCorners getPanelCorners();

public:
	Panel(PanelDimensions panelDimensions);
	virtual ~Panel() {}
	virtual void drawToScreen();
	void drawFocusedToScreen();
	void setTitle(std::string newTitle);
	void setUpperLeftCorner(Point upperLeft);
	void setLines(int newLines);
	void setColumns(int newColumns);
	void replaceWindow();
};

class ListPanel : public Panel {
public:
	ListPanel(PanelDimensions panelDimensions);
	~ListPanel();
	void drawToScreen() override;
};

class ContentPanel : public Panel {
public:
	ContentPanel(PanelDimensions panelDimensions);
	~ContentPanel();
	void drawToScreen() override;
};

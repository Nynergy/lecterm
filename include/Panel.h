#pragma once

#include "CursesUtil.h"

class Panel {
private:
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
	Panel(Point upperLeftCorner, int lines, int columns);
	~Panel();
	void drawToScreen();
	void drawFocusedToScreen();
	void setTitle(std::string newTitle);
	void setUpperLeftCorner(Point upperLeft);
	void setLines(int newLines);
	void setColumns(int newColumns);
	void replaceWindow();
};

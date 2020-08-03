#pragma once

#include "CursesUtil.h"

class Panel {
private:
	WINDOW * window;
	Point upperLeftCorner;
	int lines, columns;

	void setupWindow();
	void teardownWindow();
	void drawBorder();
	void refreshWindow();
	BoxCorners getPanelCorners();

public:
	Panel(Point upperLeftCorner, int lines, int columns);
	~Panel();
	void drawToScreen();
};

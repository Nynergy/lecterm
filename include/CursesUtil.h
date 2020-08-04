#pragma once

#include <ncurses.h>
#include <string>

#include "Points.h"

namespace CursesUtil {
	void drawCharAtPoint(char ch, Point p);
	void drawStringAtPoint(std::string text, Point p);
	void drawHorizontalLineFromAToB(Point a, Point b);
	void drawVerticalLineFromAToB(Point a, Point b);
	void drawBoxAtCorners(BoxCorners corners);
	void drawTopAndBottom(BoxCorners corners);
	void drawLeftAndRight(BoxCorners corners);
	void drawCorners(BoxCorners corners);

	int maxLines();
	int maxColumns();
}

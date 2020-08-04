#pragma once

#include <ncurses.h>
#include <string>

#include "Points.h"

// Each draw method takes the window to be drawn to, which allows these
// methods to draw to any screen, be it for a panel or just stdscr.

namespace CursesUtil {
	void drawCharAtPoint(WINDOW * win, char ch, Point p);
	void drawStringAtPoint(WINDOW * win, std::string text, Point p);
	void drawHorizontalLineFromAToB(WINDOW * win, Point a, Point b);
	void drawVerticalLineFromAToB(WINDOW * win, Point a, Point b);
	void drawBoxAtCornersWithAttribute(WINDOW * win, BoxCorners corners, int attr);
	void drawBoxAtCorners(WINDOW * win, BoxCorners corners);
	void drawTopAndBottom(WINDOW * win, BoxCorners corners);
	void drawLeftAndRight(WINDOW * win, BoxCorners corners);
	void drawCorners(WINDOW * win, BoxCorners corners);

	int maxLines();
	int maxColumns();
}

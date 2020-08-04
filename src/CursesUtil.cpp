#include "CursesUtil.h"

namespace CursesUtil {
	void drawCharAtPoint(WINDOW * win, char ch, Point p) {
		wmove(win, p.y, p.x);
		waddch(win, ch);
	}

	void drawStringAtPoint(WINDOW * win, std::string text, Point p) {
		wmove(win, p.y, p.x);
		waddstr(win, text.c_str());
	}

	void drawHorizontalLineFromAToB(WINDOW * win, Point a, Point b) {
		if(Point::pointsHaveUnequalY(a, b)) { return; }

		setWindowAttributes(win, A_ALTCHARSET);
		if(a.x < b.x) {
			for(int i = a.x; i < b.x + 1; i++) {
				drawCharAtPoint(win, ACS_HLINE, Point(i, a.y));
			}
		}

		if(a.x > b.x) {
			for(int i = b.x; i < a.x + 1; i++) {
				drawCharAtPoint(win, ACS_HLINE, Point(i, b.y));
			}
		}
		unsetWindowAttributes(win, A_ALTCHARSET);
	}

	void drawVerticalLineFromAToB(WINDOW * win, Point a, Point b) {
		if(Point::pointsHaveUnequalX(a, b)) { return; }

		setWindowAttributes(win, A_ALTCHARSET);
		if(a.y < b.y) {
			for(int i = a.y; i < b.y + 1; i++) {
				drawCharAtPoint(win, ACS_VLINE, Point(a.x, i));
			}
		}

		if(a.y > b.y) {
			for(int i = b.y; i < a.y + 1; i++) {
				drawCharAtPoint(win, ACS_VLINE, Point(b.x, i));
			}
		}
		unsetWindowAttributes(win, A_ALTCHARSET);
	}

	void drawBoxAtCornersWithAttribute(WINDOW * win, BoxCorners corners, int attr) {
		setWindowAttributes(win, attr);
		drawBoxAtCorners(win, corners);
		unsetWindowAttributes(win, attr);
	}

	void drawBoxAtCorners(WINDOW * win, BoxCorners corners) {
		drawTopAndBottom(win, corners);
		drawLeftAndRight(win, corners);
		drawCorners(win, corners);
	}

	void drawTopAndBottom(WINDOW * win, BoxCorners corners) {
		drawHorizontalLineFromAToB(win, corners.upperLeft, corners.upperRight);
		drawHorizontalLineFromAToB(win, corners.lowerLeft, corners.lowerRight);
	}

	void drawLeftAndRight(WINDOW * win, BoxCorners corners) {
		drawVerticalLineFromAToB(win, corners.upperLeft, corners.lowerLeft);
		drawVerticalLineFromAToB(win, corners.upperRight, corners.lowerRight);
	}

	void drawCorners(WINDOW * win, BoxCorners corners) {
		setWindowAttributes(win, A_ALTCHARSET);
		drawCharAtPoint(win, ACS_ULCORNER, corners.upperLeft);
		drawCharAtPoint(win, ACS_URCORNER, corners.upperRight);
		drawCharAtPoint(win, ACS_LLCORNER, corners.lowerLeft);
		drawCharAtPoint(win, ACS_LRCORNER, corners.lowerRight);
		unsetWindowAttributes(win, A_ALTCHARSET);
	}

	void setWindowAttributes(WINDOW * win, int attr) {
		wattron(win, attr);
	}

	void unsetWindowAttributes(WINDOW * win, int attr) {
		wattroff(win, attr);
	}

	int maxLines() {
		return LINES;
	}

	int maxColumns() {
		return COLS;
	}

	int getColor(std::string color) {
		if(color == "black") { return COLOR_PAIR(0); }
		else if(color == "red") { return COLOR_PAIR(1); }
		else if(color == "green") { return COLOR_PAIR(2); }
		else if(color == "yellow") { return COLOR_PAIR(3); }
		else if(color == "blue") { return COLOR_PAIR(4); }
		else if(color == "magenta") { return COLOR_PAIR(5); }
		else if(color == "cyan") { return COLOR_PAIR(6); }
		else { return COLOR_PAIR(7); }
	}
}

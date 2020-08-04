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

		wattron(win, A_ALTCHARSET);
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
		wattroff(win, A_ALTCHARSET);
	}

	void drawVerticalLineFromAToB(WINDOW * win, Point a, Point b) {
		if(Point::pointsHaveUnequalX(a, b)) { return; }

		wattron(win, A_ALTCHARSET);
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
		wattroff(win, A_ALTCHARSET);
	}

	void drawBoxAtCornersWithAttribute(WINDOW * win, BoxCorners corners, int attr) {
		wattron(win, attr);
		drawBoxAtCorners(win, corners);
		wattroff(win, attr);
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
		wattron(win, A_ALTCHARSET);
		drawCharAtPoint(win, ACS_ULCORNER, corners.upperLeft);
		drawCharAtPoint(win, ACS_URCORNER, corners.upperRight);
		drawCharAtPoint(win, ACS_LLCORNER, corners.lowerLeft);
		drawCharAtPoint(win, ACS_LRCORNER, corners.lowerRight);
		wattroff(win, A_ALTCHARSET);
	}

	int maxLines() {
		return LINES;
	}

	int maxColumns() {
		return COLS;
	}
}

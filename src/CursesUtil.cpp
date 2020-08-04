#include "CursesUtil.h"

namespace CursesUtil {
	void drawCharAtPoint(char ch, Point p) {
		mvaddch(p.y, p.x, ch);
	}

	void drawStringAtPoint(std::string text, Point p) {
		mvaddstr(p.y, p.x, text.c_str());
	}

	void drawHorizontalLineFromAToB(Point a, Point b) {
		if(Point::pointsHaveUnequalY(a, b)) { return; }

		attron(A_ALTCHARSET);
		if(a.x < b.x) {
			for(int i = a.x; i < b.x + 1; i++) {
				drawCharAtPoint(ACS_HLINE, Point(i, a.y));
			}
		}

		if(a.x > b.x) {
			for(int i = b.x; i < a.x + 1; i++) {
				drawCharAtPoint(ACS_HLINE, Point(i, b.y));
			}
		}
		attroff(A_ALTCHARSET);
	}

	void drawVerticalLineFromAToB(Point a, Point b) {
		if(Point::pointsHaveUnequalX(a, b)) { return; }

		attron(A_ALTCHARSET);
		if(a.y < b.y) {
			for(int i = a.y; i < b.y + 1; i++) {
				drawCharAtPoint(ACS_VLINE, Point(a.x, i));
			}
		}

		if(a.y > b.y) {
			for(int i = b.y; i < a.y + 1; i++) {
				drawCharAtPoint(ACS_VLINE, Point(b.x, i));
			}
		}
		attroff(A_ALTCHARSET);
	}

	void drawBoxAtCorners(BoxCorners corners) {
		drawTopAndBottom(corners);
		drawLeftAndRight(corners);
		drawCorners(corners);
	}

	void drawTopAndBottom(BoxCorners corners) {
		drawHorizontalLineFromAToB(corners.upperLeft, corners.upperRight);
		drawHorizontalLineFromAToB(corners.lowerLeft, corners.lowerRight);
	}

	void drawLeftAndRight(BoxCorners corners) {
		drawVerticalLineFromAToB(corners.upperLeft, corners.lowerLeft);
		drawVerticalLineFromAToB(corners.upperRight, corners.lowerRight);
	}

	void drawCorners(BoxCorners corners) {
		attron(A_ALTCHARSET);
		drawCharAtPoint(ACS_ULCORNER, corners.upperLeft);
		drawCharAtPoint(ACS_URCORNER, corners.upperRight);
		drawCharAtPoint(ACS_LLCORNER, corners.lowerLeft);
		drawCharAtPoint(ACS_LRCORNER, corners.lowerRight);
		attroff(A_ALTCHARSET);
	}

	int maxLines() {
		return LINES;
	}

	int maxColumns() {
		return COLS;
	}
}

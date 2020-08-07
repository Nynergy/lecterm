#pragma once

struct Point {
	int x, y;

	Point() : x(0), y(0) {}
	Point(int x, int y) : x(x), y(y) {}

	static bool pointsHaveEqualX(Point a, Point b) {
		return a.x == b.x;
	}

	static bool pointsHaveUnequalX(Point a, Point b) {
		return !pointsHaveEqualX(a, b);
	}

	static bool pointsHaveEqualY(Point a, Point b) {
		return a.y == b.y;
	}

	static bool pointsHaveUnequalY(Point a, Point b) {
		return !pointsHaveEqualY(a, b);
	}
};

struct BoxCorners {
	Point upperLeft, upperRight, lowerLeft, lowerRight;

	BoxCorners(Point ul, Point ur, Point ll, Point lr) :
		upperLeft(ul), upperRight(ur), lowerLeft(ll), lowerRight(lr) {}
};

struct PanelDimensions {
	Point upperLeft;
	int lines, columns;

	PanelDimensions(Point ul, int l, int c) :
		upperLeft(ul), lines(l), columns(c) {}
};

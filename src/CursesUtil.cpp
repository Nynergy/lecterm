#include "CursesUtil.h"

namespace CursesUtil {
	void drawCharAtPoint(char ch, Point p) {
		mvaddch(p.y, p.x, ch);
	}
}

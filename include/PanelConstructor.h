#pragma once

#include <math.h>

#include "Panel.h"

class PanelConstructor {
private:
	int calculateColumnsByRatio(float ratio);
	int calculateColumnsByOffset(int offset);

public:
	PanelConstructor();
	~PanelConstructor();
	Panel * getNewNotebookPanel();
	Panel * getNewNoteListPanel();
	Panel * getNewNotePanel();
};

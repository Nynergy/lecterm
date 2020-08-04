#pragma once

#include <math.h>

#include "Panel.h"

class PanelConstructor {
private:
	int calculateColumnsByRatio(float ratio);

public:
	PanelConstructor();
	~PanelConstructor();
	Panel * getNewNotebookPanel();
	Panel * getNewNoteListPanel();
	Panel * getNewNotePanel();
};

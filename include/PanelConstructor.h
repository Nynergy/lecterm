#pragma once

#include <math.h>
#include <vector>

#include "Panel.h"

class PanelConstructor {
private:
	int calculateColumnsByRatio(float ratio);
	int calculateColumnsByOffset(int offset);
	void resizeNotebookPanel(Panel * panel);
	void resizeNoteListPanel(Panel * panel);
	void resizeNotePanel(Panel * panel);

public:
	PanelConstructor();
	~PanelConstructor();
	Panel * getNewNotebookPanel();
	Panel * getNewNoteListPanel();
	Panel * getNewNotePanel();
	void resizePanels(std::vector<Panel *> panels);
};

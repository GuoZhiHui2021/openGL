#pragma once
#include "Render.h"

class PanelRender :public Render
{
public:
	virtual void initialize();
	virtual void render();
	//virtual void loadData(float* vertices, int vLength, float* element, int eLength);
private:
	
};


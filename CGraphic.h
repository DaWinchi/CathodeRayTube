#pragma once
#include "afxwin.h"
#include <gdiplus.h>
#include <vector>
#include <iostream>
#include "PointEl.h"

using namespace Gdiplus;
using namespace std;

class CGraphic : public CStatic
{
public:
	double xmin, xmax, ymin, ymax, step_x, step_y;

	vector<PointF> *points;

	CGraphic();
	~CGraphic();

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void Update();
	REAL X(LPDRAWITEMSTRUCT RECT, float x);
	REAL Y(LPDRAWITEMSTRUCT RECT, float y);
	REAL Width(LPDRAWITEMSTRUCT RECT, float width);
	REAL Height(LPDRAWITEMSTRUCT RECT, float height);
};


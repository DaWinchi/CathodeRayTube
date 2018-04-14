#pragma once
#include "afxwin.h"
#include <gdiplus.h>
#include <vector>
#include <iostream>
#include "PointEl.h"

using namespace Gdiplus;
using namespace std;

class CModelDraw : public CStatic
{

public:
	double xmin, xmax, ymin, ymax;

	RectangleObject *globalRectangle;
	RectangleObject *cathod;
	RectangleObject *anod1;
	RectangleObject *anod2;
	RectangleObject *conductorTop;
	RectangleObject *conductorBottom;

	vector <PointEl> *points;

	CModelDraw();
	~CModelDraw();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void Update();
	REAL X(LPDRAWITEMSTRUCT RECT, float x);
	REAL Y(LPDRAWITEMSTRUCT RECT, float y);
	REAL Width(LPDRAWITEMSTRUCT RECT, float width);
	REAL Height(LPDRAWITEMSTRUCT RECT, float height);

};


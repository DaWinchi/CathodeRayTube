#pragma once
#include "afxwin.h"
#include <gdiplus.h>
#include <vector>
#include <iostream>

using namespace Gdiplus;
typedef struct layer
{
	float *data;
	int NN;
	double shag_otrisovki_po_x;
	double first_x;
	Gdiplus::Color color;
	double pun;
};


class CModelDraw : public CStatic
{

public:
	double xmin, xmax, ymin, ymax;

	CModelDraw();
	~CModelDraw();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void Update();
	REAL X(LPDRAWITEMSTRUCT RECT, float x);
	REAL Y(LPDRAWITEMSTRUCT RECT, float y);
	REAL Width(LPDRAWITEMSTRUCT RECT, float width);
	REAL Height(LPDRAWITEMSTRUCT RECT, float height);

};

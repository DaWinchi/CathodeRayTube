#pragma once
#include "afxwin.h"
#include <gdiplus.h>
#include <vector>
#include <iostream>

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
	void transfer(double left, double right, double low, double up, double shag_setki_x, double shag_setki_y);
	float X(LPDRAWITEMSTRUCT RECT, double x);
	float Y(LPDRAWITEMSTRUCT RECT, double y);

};


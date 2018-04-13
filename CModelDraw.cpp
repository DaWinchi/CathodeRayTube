#include "stdafx.h"
#include "CModelDraw.h"
#include <math.h>

using namespace Gdiplus;

ULONG_PTR token;
CModelDraw::CModelDraw()
{
	Status s;
	GdiplusStartupInput input;
	s = GdiplusStartup(&token, &input, NULL);
	if (s != Ok)
	{
		MessageBox(L"ERROR!!!", L"Îøèáêà", MB_ICONERROR);
	}
}


CModelDraw::~CModelDraw()
{
	GdiplusShutdown(token);
}


void CModelDraw::DrawItem(LPDRAWITEMSTRUCT RECT)
{
	
	Graphics gr(RECT->hDC);
	Bitmap bmp(RECT->rcItem.right, RECT->rcItem.bottom, &gr);
	Graphics grBmp(&bmp);
	
	Pen penGlobRect(Color::White, 3);
	SolidBrush brushCathodRect(Color::Blue);
	SolidBrush brushAnodRect(Color::Red);
	SolidBrush brushConductorRect(Color::White);
	
	grBmp.Clear(Color::Black);

	grBmp.DrawRectangle(&penGlobRect, X(RECT, globalRectangle->x), Y(RECT, globalRectangle->y),
		Width(RECT, globalRectangle->width), Height(RECT, globalRectangle->height));

	grBmp.FillRectangle(&brushCathodRect, X(RECT, cathod->x), Y(RECT, cathod->y),
		Width(RECT, cathod->width), Height(RECT, cathod->height));
	
	grBmp.FillRectangle(&brushAnodRect, X(RECT, anod1->x), Y(RECT, anod1->y),
		Width(RECT, anod1->width), Height(RECT, anod1->height));

	grBmp.FillRectangle(&brushAnodRect, X(RECT, anod2->x), Y(RECT, anod2->y),
		Width(RECT, anod2->width), Height(RECT, anod2->height));


	
	
	gr.DrawImage(&bmp, 0, 0);
}


REAL CModelDraw::X(LPDRAWITEMSTRUCT RECT, float x)
{
	return (REAL)(RECT->rcItem.right) / (xmax - xmin)*((x)-xmin);
}

REAL CModelDraw::Y(LPDRAWITEMSTRUCT RECT, float y)
{
	return -(REAL)(RECT->rcItem.bottom) / (ymax - ymin)*((y)-ymax);
}

REAL CModelDraw::Width(LPDRAWITEMSTRUCT RECT, float width)
{
	return (REAL)(RECT->rcItem.right) / (xmax - xmin)*width;
}

REAL CModelDraw::Height(LPDRAWITEMSTRUCT RECT, float height)
{
	return (REAL)(RECT->rcItem.bottom) / (ymax - ymin)*height;
}

void CModelDraw::Update()
{
	Invalidate();
}
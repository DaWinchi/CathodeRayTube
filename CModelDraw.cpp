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
	
	SolidBrush brush(Color::Azure);
	
	grBmp.FillRectangle(&brush, X(RECT, -50), Y(RECT, 50), Width(RECT, 100), Height(RECT, 100));

	
	
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
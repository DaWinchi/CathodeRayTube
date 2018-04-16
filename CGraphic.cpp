#include "stdafx.h"
#include "CGraphic.h"
#include <math.h>

using namespace Gdiplus;

ULONG_PTR token;
CGraphic::CGraphic()
{
	Status s;
	GdiplusStartupInput input;
	s = GdiplusStartup(&token, &input, NULL);
	if (s != Ok)
	{
		MessageBox(L"ERROR!!!", L"Îøèáêà", MB_ICONERROR);
	}
}


CGraphic::~CGraphic()
{
	GdiplusShutdown(token);
}


void CGraphic::DrawItem(LPDRAWITEMSTRUCT RECT)
{

	Graphics gr(RECT->hDC);
	Bitmap bmp(RECT->rcItem.right, RECT->rcItem.bottom, &gr);
	Graphics grBmp(&bmp);

	Pen penGlobRect(Color::White, 3);
	SolidBrush brushCathodRect(Color::Blue);
	SolidBrush brushAnodRect(Color::Red);
	SolidBrush brushConductorRect(Color::DarkKhaki);

	grBmp.Clear(Color::Black);

	
	gr.DrawImage(&bmp, 0, 0);
}


REAL CGraphic::X(LPDRAWITEMSTRUCT RECT, float x)
{
	return (REAL)(RECT->rcItem.right) / (xmax - xmin)*((x)-xmin);
}

REAL CGraphic::Y(LPDRAWITEMSTRUCT RECT, float y)
{
	return -(REAL)(RECT->rcItem.bottom) / (ymax - ymin)*((y)-ymax);
}

REAL CGraphic::Width(LPDRAWITEMSTRUCT RECT, float width)
{
	return (REAL)(RECT->rcItem.right) / (xmax - xmin)*width;
}

REAL CGraphic::Height(LPDRAWITEMSTRUCT RECT, float height)
{
	return (REAL)(RECT->rcItem.bottom) / (ymax - ymin)*height;
}

void CGraphic::Update()
{
	Invalidate();
}
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
	Graphics gr_bmp(&bmp);
	
	
	
	gr.DrawImage(&bmp, 0, 0);
}







float CModelDraw::X(LPDRAWITEMSTRUCT RECT, double x)
{
	return (float)(RECT->rcItem.right) / (float)(xmax - xmin)*((x)-xmin);
}

float CModelDraw::Y(LPDRAWITEMSTRUCT RECT, double y)
{
	return -(float)(RECT->rcItem.bottom) / (float)(ymax - ymin)*((y)-ymax);
}
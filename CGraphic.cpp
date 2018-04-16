#include "stdafx.h"
#include "CGraphic.h"
#include <math.h>

using namespace Gdiplus;

ULONG_PTR token2;
CGraphic::CGraphic()
{
	Status s;
	GdiplusStartupInput input;
	s = GdiplusStartup(&token2, &input, NULL);
	if (s != Ok)
	{
		MessageBox(L"ERROR!!!", L"Ошибка", MB_ICONERROR);
	}
}


CGraphic::~CGraphic()
{
	GdiplusShutdown(token2);
}


void CGraphic::DrawItem(LPDRAWITEMSTRUCT RECT)
{

	Graphics gr(RECT->hDC);
	Bitmap bmp(RECT->rcItem.right, RECT->rcItem.bottom, &gr);
	Graphics grBmp(&bmp);

	FontFamily podpis_osi(L"Arial");
	Gdiplus::Font podpis(&podpis_osi, 12, FontStyleRegular, UnitPixel);

	SolidBrush brush(Color::White);
	Pen graph_pen(Color::Red, 3);
	Pen osi_pen(Color::White, 2);
	Pen setka_pen(Color::White, 1);
	setka_pen.SetDashStyle(DashStyle::DashStyleDash);

	grBmp.SetSmoothingMode(SmoothingModeAntiAlias);
	grBmp.Clear(Color::Black);


	//главные оси
	grBmp.DrawLine(&osi_pen, X(RECT, xmin), Y(RECT, 0), X(RECT, xmax), Y(RECT, 0));
	grBmp.DrawLine(&osi_pen, X(RECT, 0), Y(RECT, ymin), X(RECT, 0), Y(RECT, ymax));

	//сетка
	//вертикальные линии
	for (double x = step_x; x <= xmax; x += step_x)
	{
		grBmp.DrawLine(&setka_pen, X(RECT, x), Y(RECT, ymin), X(RECT, x), Y(RECT, ymax));
	}
	for (double x = -step_x; x >= xmin; x -= step_x)
	{
		grBmp.DrawLine(&setka_pen, X(RECT, x), Y(RECT, ymin), X(RECT, x), Y(RECT, ymax));
	}

	//горизонтальные линии
	for (double y = step_y; y <= ymax; y += step_y)
	{
		grBmp.DrawLine(&setka_pen, X(RECT, xmin), Y(RECT, y), X(RECT, xmax), Y(RECT, y));
	}
	for (double y = -step_y; y >= ymin; y -= step_y)
	{
		grBmp.DrawLine(&setka_pen, X(RECT, xmin), Y(RECT, y), X(RECT, xmax), Y(RECT, y));
	}

	//подпись точек на горизонтали
	for (double x = step_x; x <= xmax; x += step_x)
	{
		CString str;
		str.Format(_T("%.3f"), x);
		grBmp.DrawString(str, -1, &podpis, PointF(X(RECT, x), Y(RECT, 0) + 2.f), NULL, &brush);
	}
	for (double x = -step_x; x >= xmin; x -= step_x)
	{
		CString str;
		str.Format(_T("%.3f"), x);
		grBmp.DrawString(str, -1, &podpis, PointF(X(RECT, x), Y(RECT, 0) + 2.f), NULL, &brush);
	}

	//подпись точек на вертикали
	for (double y = step_y; y <= ymax; y += step_y)
	{
		CString str;
		str.Format(_T("%.1f"), y);
		grBmp.DrawString(str, -1, &podpis, PointF(X(RECT, 0), Y(RECT, y) + 2.f), NULL, &brush);
	}
	for (double y = 0; y >= ymin; y -= step_y)
	{
		CString str;
		str.Format(_T("%.1f"), y);
		grBmp.DrawString(str, -1, &podpis, PointF(X(RECT, 0), Y(RECT, y) + 2.f), NULL, &brush);
	}
	if (points != nullptr)
	{
		int size = points->size();
		for (int i = 0; i < size-1; ++i)
		{
			grBmp.DrawLine(&graph_pen, X(RECT, points[0][i].X), Y(RECT, points[0][i].Y),
				X(RECT, points[0][i + 1].X), Y(RECT, points[0][i + 1].Y));
		}
	}
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
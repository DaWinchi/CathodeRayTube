#include "stdafx.h"
#include "CCalculate.h"
#include <time.h>


CCalculate::CCalculate()
{
	srand(time(NULL));
}

CCalculate::CCalculate(vector <PointEl> *points)
{
	this->points = points;
}
CCalculate::~CCalculate()
{
}

void CCalculate::GeneratePoints()
{
	for (int i = 0; i < countGneratepoints; ++i)
	{
		PointEl pt;
		pt.x = cathod->x + cathod->width;
		pt.y = (double)rand() / RAND_MAX*(cathod->height - cathod->y) * 2 - (cathod->height - cathod->y);
		pt.dx = (double)(rand() % 101);
		pt.dy = (double)(rand() % 401 - 200);
		points->push_back(pt);
	}
}

void CCalculate::CalculateSystem(double stepTime)
{
	omp_set_num_threads(omp_get_num_procs());

	GeneratePoints();

	int sizePoints = points[0].size();

	double *forcesX = new double[sizePoints];
	double *forcesY = new double[sizePoints];

#pragma omp parallel for	
	for (int i = 0; i < sizePoints; ++i)
	{
		forcesX[i] = 0;
		forcesY[i] = 0;
		for (int j = 0; j < sizePoints; ++j)
		{
			if (i == j) continue;
			else
			{
				forcesX[i] += ForceX(points[0][i].x, points[0][j].x) / M;
				forcesY[i] += ForceY(points[0][i].y, points[0][j].y) / M;
			}
		}
		forcesX[i] += ForceCathodAnod(points[0][i].y);

	}

#pragma omp parallel for
	for (int i = 0; i < sizePoints; ++i)
	{
		points[0][i].x = points[0][i].x +
			points[0][i].dx*stepTime + forcesX[i] * stepTime*stepTime / 2;
		points[0][i].y = points[0][i].y +
			points[0][i].dy*stepTime + forcesY[i] * stepTime*stepTime / 2;
		points[0][i].dx = points[0][i].dx + forcesX[i] * stepTime;
		points[0][i].dy = points[0][i].dy + forcesY[i] * stepTime;
	}

	delete[]forcesX;
	delete[]forcesY;
	TerminatePoints();
}

double CCalculate::ForceX(double x1, double x2)
{
	if (fabs(x1 - x2) < 1e-6) return 0;
	if (x2 > x1) return -K*Q*Q / (x1 - x2) / (x1 - x2);
	else return K*Q*Q / (x1 - x2) / (x1 - x2);

}
double CCalculate::ForceY(double y1, double y2)
{
	if (fabs(y1 - y2) < 1e-6) return 0;
	if (y2 > y1)  return -K*Q*Q / (y1 - y2) / (y1 - y2);
	else return K*Q*Q / (y1 - y2) / (y1 - y2);

}

double CCalculate::ForceCathodAnod(double y)
{
	if (y<cathod->y&&y>(cathod->y - cathod->height))
	{
		double value = (Uan - Ucat) / fabs((cathod->x + cathod->width) - anodTop->x);
		return value*Q;
	}
	else return 0;
}

double CCalculate::ForceConductor(double x)
{
	if (x > conductorTop->x&&x < (conductorTop->x + conductorTop->width))
	{

	}
	return 0;
}

void CCalculate::CalculateInit(double stepTime)
{
	GeneratePoints();
	points[0][0].x = points[0][0].dx*stepTime;
	points[0][0].y = points[0][0].dy*stepTime;
}

void CCalculate::TerminatePoints()
{
	int sizePoints = points[0].size();
	vector <PointEl> newPoints;
	//#pragma omp parallel for
	for (int i = 0; i < sizePoints; ++i)
	{
		bool IsOk = true;
		if ((points[0][i].x > (globalRectangle->x + globalRectangle->width)) ||
			(points[0][i].x < (cathod->x + cathod->width) )||
			(points[0][i].y < (globalRectangle->y - globalRectangle->height)) ||
			(points[0][i].y > globalRectangle->y)) IsOk = false;

		if ((points[0][i].x < anodTop->x)&&
			(points[0][i].y > (anodTop->y - anodTop->height))) IsOk = false;

		if ((points[0][i].x < anodBottom->x) &&
			(points[0][i].y <anodBottom->y)) IsOk = false;

		if(IsOk)
		{
			newPoints.push_back(points[0][i]);
		}
	}

	points->swap(newPoints);
}
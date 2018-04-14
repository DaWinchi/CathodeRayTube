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
		pt.y = (double)rand()/RAND_MAX*(cathod->height - cathod->y)*2- (cathod->height - cathod->y);
		pt.dx = (double)(rand() % 201);
		pt.dy = (double)(rand() % 41 - 20);
		points->push_back(pt);
	}
}

void CCalculate::CalculateSystem(double stepTime)
{
	omp_set_num_threads(omp_get_num_procs());

	GeneratePoints();

	int sizePoints = points->size();

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
					forcesX[i] += ForceX(points[0][i].x, points[0][j].x);
					forcesY[i] += ForceY(points[0][i].y, points[0][j].y);
				}
			}
		}
	

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
	if(x2>x1) return -K*Q*Q / (x1 - x2) / (x1 - x2);
	else return K*Q*Q / (x1 - x2) / (x1 - x2);
	
}
double CCalculate::ForceY(double y1, double y2)
{
	if (fabs(y1 - y2) < 1e-6) return 0;
	if(y2>y1)  return -K*Q*Q / (y1 - y2) / (y1 - y2);
	else return K*Q*Q / (y1 - y2) / (y1 - y2);
	
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
	for (int i = 0; i < sizePoints; ++i)
	{
		if (points[0][i].x<(globalRectangle->x + globalRectangle->width) &&
			points[0][i].x>globalRectangle->x &&
			points[0][i].y > (globalRectangle->y - globalRectangle->height) &&
			points[0][i].y < globalRectangle->y)
		{
			newPoints.push_back(points[0][i]);
		}
	}

	points[0].clear();
	points[0].resize(newPoints.size());
	points[0] = newPoints;
		
}
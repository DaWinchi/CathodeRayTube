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
		PointEl pt;
		points[0][i].dx = forcesX[i] / M*stepTime;
		points[0][i].dy = forcesY[i] / M*stepTime;
		points[0][i].x = points[0][i].dx*stepTime;
		points[0][i].y = points[0][i].dy*stepTime;
	}

	delete[]forcesX;
	delete[]forcesY;
}

double CCalculate::ForceX(double x1, double x2)
{
	if (fabs(x1 - x2) < 1e-6) return 0;
	return K*Q*Q / (x1 - x2) / (x1 - x2);
}
double CCalculate::ForceY(double y1, double y2)
{
	if (fabs(y1 - y2) < 1e-6) return 0;
	return K*Q*Q / (y1 - y2) / (y1 - y2);
}
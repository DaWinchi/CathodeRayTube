#include "stdafx.h"
#include "CCalculate.h"
#include <time.h>

#define M_PI 3.14159265358

CCalculate::CCalculate()
{
	srand(time(NULL));
}

CCalculate::CCalculate(vector <PointEl> *points, vector<PointF> *pointsGraph)
{
	this->points = points;
	this->pointsGraph = pointsGraph;
	alltime = 0;

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
		pt.dx = (double)(rand() % 201);
		pt.dy = (double)(rand() % 41 - 20);;
		points->push_back(pt);
	}
}

void CCalculate::CalculateSystem(double stepTime)
{
	omp_set_num_threads(omp_get_num_procs());

	GeneratePoints();

	w = 2.f*M_PI / 1200.f / stepTime; //������� ������
	UpdateU();

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
				forcesX[i] += ForceX(points[0][i].x, points[0][j].x, points[0][i].y, points[0][j].y) / M;
				forcesY[i] += ForceY(points[0][i].x, points[0][j].x, points[0][i].y, points[0][j].y) / M;
			}
		}
		forcesX[i] += ForceCathodAnod(points[0][i].y);
		forcesY[i] += ForceConductor(points[0][i].x);
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
	TerminatePoints(stepTime);

	alltime += stepTime;
}

double CCalculate::ForceX(double x1, double x2, double y1, double y2)
{
	if (fabs(x1 - x2) < 1e-6) return 0;
	else return K*Q*Q / ((x1 - x2) * (x1 - x2)+(y1-y2)*(y1-y2))*(x1-x2)/fabs(x1-x2);

}
double CCalculate::ForceY(double x1, double x2, double y1, double y2)
{
	if (fabs(y1 - y2) < 1e-6) return 0;
	else  return K*Q*Q/((x1 - x2) * (x1 - x2) + (y1 - y2)*(y1 - y2))*(y1 - y2) / fabs(y1 - y2);
	
}

double CCalculate::ForceCathodAnod(double x)
{
	if (x>(cathod->x+cathod->width)&&x<anodTop->x)
	{
		double value = (Uan - Ucat) / fabs((cathod->x + cathod->width) - anodTop->x);
		return value;
	}
	else return 0;
}

double CCalculate::ForceConductor(double x)
{
	int sizecond = sinusUtop.size();
	double value = 0;
	if (x > conductorTop->x && x < (conductorTop->x + conductorTop->width))
	{
		if (Ucon1 > Ucon2)
		{
			value += (Ucon1 - Ucon2) / (globalRectangle->height);
		}
		else
		{
			value += (Ucon1 - Ucon2) / (globalRectangle->height);
		}
	}

	return value;
}

void CCalculate::CalculateInit(double stepTime)
{
	GeneratePoints();
	points[0][0].x = points[0][0].dx*stepTime;
	points[0][0].y = points[0][0].dy*stepTime;
}

void CCalculate::TerminatePoints(double stepTime)
{
	int sizePoints = points[0].size();
	int countDispersingPoints = 0;
	double summY = 0;
	vector <PointEl> newPoints;
	//#pragma omp parallel for
	for (int i = 0; i < sizePoints; ++i)
	{
		//����������� �����
		if (fabs(points[0][i].y) <= globalRectangle->y&&points[0][i].x > (globalRectangle->x + globalRectangle->width))
		{
			summY += points[0][i].y;
			++countDispersingPoints;
		}
		//�������� ����� �� ����� �� ����
		bool IsOk = true;
		if ((points[0][i].x > (globalRectangle->x + globalRectangle->width)) ||
			(points[0][i].x < (cathod->x + cathod->width)) ||
			(points[0][i].y < (globalRectangle->y - globalRectangle->height)) ||
			(points[0][i].y > globalRectangle->y)) IsOk = false;

		if ((points[0][i].x < anodTop->x) &&
			(points[0][i].y > (anodTop->y - anodTop->height))) IsOk = false;

		if ((points[0][i].x < anodBottom->x) &&
			(points[0][i].y < anodBottom->y)) IsOk = false;

		if (IsOk)
		{
			newPoints.push_back(points[0][i]);
		}
	}

	if (countDispersingPoints > 0)
	{
		PointF pt;
		pt.X = alltime;
		pt.Y = (double)summY / countDispersingPoints;

		pointsGraph[0].push_back(pt);
	}
	
	points->swap(newPoints);


}

void CCalculate::UpdateU()
{
	Ucon1 = Uampl_cond*sin(w*alltime);
	Ucon2 = -Ucon1;
}
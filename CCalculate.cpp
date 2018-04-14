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

void CCalculate::GeneratorPoints()
{
	for (int i = 0; i < countGneratepoints; ++i)
	{
		PointEl pt;
		pt.x = cathod->x + cathod->width;
		pt.y = (double)(rand() % ((int)(cathod->height))+cathod->y);
		pt.dx = (double)(rand() % 201);
		pt.dy = (double)(rand() % 401 - 200);
		points->push_back(pt);
	}
}

void CCalculate::CalculateSystem(double stepTime)
{
	double m = 2 * K;

}

double CCalculate::ForceX(double x)
{	
	return K*Q*Q / x / x;
}
double CCalculate::ForceY(double y)
{
	return K*Q*Q / y / y;
}
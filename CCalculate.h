#pragma once
#include <vector>
#include <omp.h> 
#include "PointEl.h"

#define K 9e+9
#define Q 1.60217662e-19
#define M 9.10938356e-31

using namespace std;


class CCalculate
{
public:
	
	int countGneratepoints;
	vector<PointEl> *points;
	RectangleObject *cathod;

	void GeneratePoints();
	void CalculateSystem(double stepTime);
	CCalculate();
	CCalculate(vector <PointEl> *points);
	double ForceX(double x1, double x2);
	double ForceY(double y1, double y2);
	~CCalculate();
};


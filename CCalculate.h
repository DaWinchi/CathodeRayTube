#pragma once
#include <vector>
#include "CModelDraw.h"

#define K 9e+9
#define E 1.60217662e-19

using namespace std;


struct PointEl
{
	double x;
	double y;
	double dx;
	double dy;
};

class CCalculate
{
public:
	
	int countGneratepoints;
	vector<PointEl> *points;
	RectangleObject *cathod;

	void GeneratorPoints();
	void CalculateSystem(double stepTime);
	CCalculate();
	CCalculate(vector <PointEl> *points);
	~CCalculate();
};


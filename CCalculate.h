#pragma once
#include <vector>

using namespace std;

struct RectangleObject
{
	float x, y, width, height;
};

struct Point
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
	vector<Point> *points;
	RectangleObject *cathod;

	void GeneratorPoints();
	CCalculate();
	~CCalculate();
};


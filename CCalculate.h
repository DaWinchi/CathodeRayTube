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


	double Ucat, Uan, Ucon1, Ucon2;

	int countGneratepoints;
	vector<PointEl> *points;
	RectangleObject *globalRectangle;
	RectangleObject *cathod;
	RectangleObject *anodTop;
	RectangleObject *anodBottom;
	RectangleObject *conductorTop;
	RectangleObject *conductorBottom;

	vector<SinusU> sinusU;


	void GeneratePoints();
	void CalculateSystem(double stepTime);
	CCalculate();
	CCalculate(vector <PointEl> *points);
	void TerminatePoints();
	void CalculateInit(double stepTime);
	double ForceX(double x1, double x2);
	double ForceY(double y1, double y2);
	void CreateSinusU();
	double ForceCathodAnod(double y);
	double ForceConductor(double x);
	~CCalculate();
};


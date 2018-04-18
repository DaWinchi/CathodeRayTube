#pragma once
#include <vector>
#include <omp.h> 
#include "PointEl.h"

#define K 9e+9
#define Q 1.60217662e-19
#define M 9.10938356e-31

using namespace std;
using namespace Gdiplus;

class CCalculate
{
public:


	double Ucat, Uan, Ucon1, Ucon2, Uampl_cond;
	int countGneratepoints;
	vector<PointEl> *points;
	vector<PointF> *pointsGraph;


	RectangleObject *globalRectangle;
	RectangleObject *cathod;
	RectangleObject *anodTop;
	RectangleObject *anodBottom;
	RectangleObject *conductorTop;
	RectangleObject *conductorBottom;

	vector<SinusU> sinusUtop;
	vector<SinusU> sinusUbottom;

	double alltime;
	double w;

	void GeneratePoints();
	void CalculateSystem(double stepTime);
	CCalculate();
	CCalculate(vector <PointEl> *points, vector <PointF> *pointsGraph);
	void TerminatePoints(double stepTime);
	void CalculateInit(double stepTime);
	double ForceX(double x1, double x2, double y1, double y2);
	double ForceY(double x1, double x2, double y1, double y2);
	void UpdateU();
	double ForceCathodAnod(double x);
	double ForceConductor(double x);
	~CCalculate();
};


#include "stdafx.h"
#include "CCalculate.h"
#include <time.h>


CCalculate::CCalculate()
{
	srand(time(NULL));
}


CCalculate::~CCalculate()
{
}

void CCalculate::GeneratorPoints()
{
	for (int i = 0; i < countGneratepoints; ++i)
	{
		Point pt;
		pt.x = cathod->x + cathod->width;
		pt.y = rand() % ((int)(cathod->height))+cathod->y;
		points->push_back(pt);
	}
}
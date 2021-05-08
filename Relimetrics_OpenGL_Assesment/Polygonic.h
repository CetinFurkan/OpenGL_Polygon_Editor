#pragma once
#ifndef POLYGONIC_H
#define POLYGONIC_H

//#include "Common.h"
#include "MathHelper.h"
#include "Point.h"


class Polygonic
{
public:
	Polygonic();

	virtual void addPoint(Point) = 0;
	virtual Point getFirstPoint() = 0;
	virtual Point getLastPoint() = 0;
	virtual Point getPoint(int) = 0;
	virtual int getSize() = 0;
	
};

#endif POLYGONIC_H
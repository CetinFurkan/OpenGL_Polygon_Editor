#pragma once
#ifndef POLYGONICARRAY_H
#define POLYGONICARRAY_H

#include "PolygonParent.h"


class PolygonArray: public PolygonParent
{
public:
	PolygonArray(int _size);

	void addPoint(Point);
	Point getFirstPoint();
	Point getLastPoint();
	Point getPoint(int);
	int getSize();

protected:
	Point *listPoints;
	unsigned int size = 0;
	unsigned int index = 0;
	
};

#endif POLYGONICARRAY_H
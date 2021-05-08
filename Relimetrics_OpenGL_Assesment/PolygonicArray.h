#pragma once
#ifndef POLYGONICARRAY_H
#define POLYGONICARRAY_H

#include "Polygonic.h"


class PolygonicArray: public Polygonic
{
public:
	PolygonicArray(int _size);

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
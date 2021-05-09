#pragma once
#ifndef POLYGONPARENT_H
#define POLYGONPARENT_H

#include "Point.h"


class PolygonParent
{
public:
	PolygonParent();

	virtual void addPoint(Point) = 0;
	virtual Point getFirstPoint() = 0;
	virtual Point getLastPoint() = 0;
	virtual Point getPoint(int) = 0;
	virtual int getSize() = 0;
	
};

#endif POLYGONPARENT_H
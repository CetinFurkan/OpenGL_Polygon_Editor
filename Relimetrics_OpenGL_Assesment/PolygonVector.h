#pragma once
#ifndef POLYGONVECTOR_H
#define POLYGONVECTOR_H

#include "PolygonParent.h"
#include <vector>

using namespace std;

class PolygonVector : public PolygonParent
{
public:
	PolygonVector();

	void addPoint(Point);
	Point getFirstPoint();
	Point getLastPoint();
	Point getPoint(int);
	int getSize();

	void clearData();

protected:
	vector<Point> listPoints;
	unsigned int size = 0;
};

#endif POLYGONVECTOR_H
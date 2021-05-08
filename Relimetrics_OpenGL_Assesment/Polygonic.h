#pragma once
#ifndef POLYGONIC_H
#define POLYGONIC_H

#include "Common.h"
#include "MathHelper.h"


class Polygonic
{
public:
	Polygonic();

	void addPoint(Point*);
	void addPoint(float, float);

	Point* getLastPoint();

	bool checkPointIsCloseToFirstPoint(Point * _p);

	bool checkIfClosed();
	
protected:

	vector<Point*> listPoint;
	unsigned int size = 0;

	bool isClosed = false;

	friend class GLDrawer;
};

#endif POLYGONIC_H
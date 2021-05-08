#pragma once
#ifndef POLYGONIC_H
#define POLYGONIC_H

#include "Common.h"
#include "Point.h"
#include "MathHelper.h"

class Polygonic
{
	Polygonic();

public:
	void addPoint(Point*);
	void addPoint(float, float);
	
private:
	Point* pos;
	std::vector<Point*> listPoint;

	bool updateIsClosed();
	bool isClosed = false;


};

#endif POLYGONIC_H
#include "Polygonic.h"

Polygonic::Polygonic() {

}

void Polygonic::addPoint(Point* _pointNewToAdd)
{
	listPoint.push_back(_pointNewToAdd);
	size += 1;
}

void Polygonic::addPoint(float _x, float _y) {
	listPoint.push_back(new Point(_x,_y));
	size += 1;
}

Point* Polygonic::getLastPoint() {
	return listPoint[size - 1];
}

bool Polygonic::checkPointIsCloseToFirstPoint(Point* _p)
{
	if (size <= 2)
		return false;

	return (dist(_p, listPoint[0]) < 5.0f);
}

bool Polygonic::checkIfClosed()
{
	if (size <= 2)
		return false;

	return (dist(listPoint[0], listPoint[size-1]) < 5.0f);
}


#include "PolygonVector.h"

PolygonVector::PolygonVector()
{
}

void PolygonVector::addPoint(Point _pointNewToAdd)
{
	listPoints.push_back(_pointNewToAdd);
}

Point PolygonVector::getFirstPoint()
{
	return *listPoints.begin();
}

Point PolygonVector::getLastPoint()
{
	return *listPoints.end();
}

Point PolygonVector::getPoint(int _index)
{
	return listPoints[_index];
}

int PolygonVector::getSize()
{
	return listPoints.size();
}

void PolygonVector::clearData()
{
	listPoints.clear();
}

#include "PolygonArray.h"


PolygonArray::PolygonArray(int _size)
{
	listPoints = new Point[_size];
	size = _size;
}

void PolygonArray::addPoint(Point _pointNewToAdd)
{
	listPoints[index] = _pointNewToAdd;
	index++;
}

Point PolygonArray::getFirstPoint() {
	return listPoints[0];
}

Point PolygonArray::getLastPoint() {
	return listPoints[size - 1];
}

Point PolygonArray::getPoint(int _index)
{
	return listPoints[_index];
}

int PolygonArray::getSize()
{
	return size;
}


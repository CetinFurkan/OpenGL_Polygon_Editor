#include "PolygonicArray.h"



PolygonicArray::PolygonicArray(int _size)
{
	listPoints = new Point[_size];
}

void PolygonicArray::addPoint(Point _pointNewToAdd)
{
	listPoints[index] = _pointNewToAdd;
	index++;
}

Point PolygonicArray::getFirstPoint() {
	return listPoints[0];
}

Point PolygonicArray::getLastPoint() {
	return listPoints[size - 1];
}

Point PolygonicArray::getPoint(int _index)
{
	return listPoints[_index];
}

int PolygonicArray::getSize()
{
	return size;
}


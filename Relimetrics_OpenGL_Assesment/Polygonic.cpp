#include "Polygonic.h"

Polygonic::Polygonic() {

	cout << "Polygonic is initialized";
}

void Polygonic::addPoint(Point* _newPoint)
{
	listPoint.push_back(_newPoint);
}

void Polygonic::addPoint(float _x, float _y) {
	listPoint.push_back(new Point(_x,_y));
}

bool Polygonic::updateIsClosed()
{
	return (dist(*listPoint.begin(), *listPoint.end()) < 0.1f);
}


#include "Point.h"

Point::Point() {
	x = 0;
	y = 0;
}
Point::Point(float _x, float _y) {
	x = _x;
	y = _y;
}


void Point::setX(float _x) {
	x = _x;
}
void Point::setY(float _y) {
	y = _y;
}
void Point::setXY(float _x, float _y) {
	x = _x;
	y = _y;
}



void Point::setRelX(float _x) {
	x += _x;
}
void Point::setRelY(float _y) {
	y += _y;
}
void Point::setRelXY(float _x, float _y) {
	x += _x;
	y += _y;
}



void Point::setXYfromPoint(Point *_p)
{
	x = _p->getX();
	y = _p->getY();
}

void Point::setRelXYfromPoint(Point *_p)
{
	x += _p->getX();
	y += _p->getY();
}



float Point::getX()
{
	return x;
}

float Point::getY()
{
	return y;
}


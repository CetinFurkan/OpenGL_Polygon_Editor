#include "Point.h"

Point::Point() {
	x = 0;
	y = 0;
}
Point::Point(float _x, float _y) {
	x = _x;
	y = _y;
}
Point::Point(int _x, int _y) {
	x = _x;
	y = _y;
}

void Point::setXf(float _x) {
	x = _x;
}
void Point::setYf(float _y) {
	y = _y;
}
void Point::setXYf(float _x, float _y) {
	x = _x;
	y = _y;
}

void Point::setX(int _x) {
	x = _x;
}

void Point::setY(int _y) {
	y = _y;
}

void Point::setXY(int _x, int _y) {
	x = _x;
	y = _y;
}


void Point::setRelXf(float _x) {
	x += _x;
}
void Point::setRelYf(float _y) {
	y += _y;
}
void Point::setRelXYf(float _x, float _y) {
	x += _x;
	y += _y;
}

void Point::setRelX(int _x) {
	x += _x;
}

void Point::setRelY(int _y) {
	y += _y;
}

void Point::setRelXY(int _x, int _y) {
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


int Point::getX()
{
	return int(x);
}

int Point::getY()
{
	return int(y);
}

float Point::getXf()
{
	return x;
}

float Point::getYf()
{
	return y;
}


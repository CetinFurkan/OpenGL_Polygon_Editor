#pragma once
#include <cmath>
#include <cstdlib>
#include "Point.h"

static float dist(Point* _a, Point* _b) {
	return sqrt(pow(_a->getX() - _b->getX(), 2.0) + pow(_a->getY() - _b->getY(), 2.0));
}

static float limit(float _val, float _min, float _max) {
	if (_val > _max)
		_val = _max;
	else if (_val < _min)
		_val = _min;

	return _val;
}
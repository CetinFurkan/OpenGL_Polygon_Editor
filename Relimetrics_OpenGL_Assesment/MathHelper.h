#pragma once
#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <cmath>
#include <cstdlib>
#include "Point.h"

using namespace std;

#define  M_PI 3.14159265359

#ifndef degtorad
#define  degtorad(a)    a*0.01745329252
#endif

#ifndef radtodeg
#define  radtodeg(a)    a/0.01745329252
#endif

#ifndef max
#define  max(a,b)       (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define  min(a,b)       (((a) < (b)) ? (a) : (b))
#endif

#ifndef limit
#define limit(v,n,x)    max(n, min(x, v))
#endif

#ifndef sign
#define  sign(v)         ((_v > 0) - (_v < 0))
#endif


static float isInsidePointInRect(Point _a, float _x, float _y, float _w, float _h) {
	//checking each boundry one by one and this is the most efficient way
	if (_a.x > _x)
		if (_a.x < _x + _w)
			if (_a.y > _y)
				if (_a.y < _y + _h)
					return true;

	return false;
}

static float isInsidePointInCircle(Point _a, float _x, float _y, float _r) {
	//distance to the center ofthe circle
	return sqrt(pow(_a.x - _x, 2.0) + pow(_a.y - _y, _r));
}


static float dist(Point _a, Point _b) {
	return sqrt(pow(_a.x - _b.x, 2.0) + pow(_a.y - _b.y, 2.0));
}


#endif MATHHELPER_H
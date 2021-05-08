#pragma once
#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <cmath>
#include <cstdlib>

#include "Point.h"

using namespace std;

#define  M_PI 3.14159265359

#ifndef degtorad
#define  degtorad(a)           a*0.01745329252
#endif

#ifndef radtodeg
#define  radtodeg(a)           a/0.01745329252
#endif

#ifndef max
#define  max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define  min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef limit
#define limit(v,n,x)       max(n, min(x, v))
#endif

#ifndef sign
#define  sign(v)            ((_v > 0) - (_v < 0))
#endif

static float dist(Point* _a, Point* _b) {
	return sqrt(pow(_a->getX() - _b->getX(), 2.0) + pow(_a->getY() - _b->getY(), 2.0));
}


#endif MATHHELPER_H
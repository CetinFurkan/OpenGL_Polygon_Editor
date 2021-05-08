#pragma once
#ifndef POINT_H
#define POINT_H

struct PointData {
	float x;
	float y;
};

class Point
{
public:
	Point();
	Point(float, float);
	Point(Point*);

	void setX(float);
	void setY(float);
	void setXY(float, float);

	void setRelX(float);
	void setRelY(float);
	void setRelXY(float, float);

	void setXYfromPoint(Point*);
	void setRelXYfromPoint(Point*);

	float getX();
	float getY();

private:
	float x, y;
};

#endif POINT_H
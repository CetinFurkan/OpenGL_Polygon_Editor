#pragma once
#ifndef POINT_H
#define POINT_H

class Point
{
public:
	Point();
	Point(float, float);
	Point(int, int);

	void setXf(float);
	void setYf(float);
	void setXYf(float, float);

	void setX(int);
	void setY(int);
	void setXY(int, int);

	void setRelXf(float);
	void setRelYf(float);
	void setRelXYf(float, float);

	void setRelX(int);
	void setRelY(int);
	void setRelXY(int, int);

	void setXYfromPoint(Point*);
	void setRelXYfromPoint(Point*);

	int getX();
	int getY();

	float getXf();
	float getYf();

private:
	float x, y;
};

#endif POINT_H
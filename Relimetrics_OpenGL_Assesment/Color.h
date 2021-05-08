#pragma once
#ifndef COLOR_H
#define COLOR_H

typedef struct {
	float r;
	float g;
	float b;
	float alpha;
}ColorData;

class Color
{
public:
	Color();
	Color(float);
	Color(float, float, float);
	Color(float, float, float, float);

	void setColor(float);
	void setColor(float, float, float);
	void setAll(float, float, float, float);
	void setAll(Color*);
	void setAll(ColorData);

	void setR(float);
	void setG(float);
	void setB(float);
	void setAlpha(float);

	float getR();
	float getG();
	float getB();
	float getAlpha();

private:
	ColorData colorData;
};

#endif COLOR_H
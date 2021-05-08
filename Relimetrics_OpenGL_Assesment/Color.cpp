#include "Color.h"
#include "MathHelper.h"


Color::Color() {
	setAll(255.0, 255.0, 255.0, 255.0);
}
Color::Color(float _v) {
	setColor(_v);
	setAlpha(255.0);
}
Color::Color(float _r, float _g, float _b) {
	setAll(_r, _g, _b, 255.0);
}
Color::Color(float _r, float _g, float _b, float _alpha) {
	setAll(_r, _g, _b, _alpha);
}

void Color::setColor(float _v) {
	setColor(_v, _v, _v);
}
void Color::setColor(float _r, float _g, float _b) {
	setR(_r);
	setG(_g);
	setB(_b);
}
void Color::setAll(float _r, float _g, float _b, float _alpha) {
	setColor(_r, _g, _b);
	setAlpha(_alpha);
}
void Color::setAll(Color* _col) {
	setColor(_col->colorData.r, _col->colorData.g, _col->colorData.b);
	setAlpha(_col->colorData.alpha);
}

void Color::setAll(ColorData _colordata)
{
	setColor(_colordata.r, _colordata.g, _colordata.b);
	setAlpha(_colordata.alpha);
}

void Color::setR(float _r) {
	colorData.r = limit(_r, 0.0, 255.0);
}

void Color::setG(float _g) {
	colorData.g = limit(_g, 0.0, 255.0);
}

void Color::setB(float _b) {
	colorData.b = limit(_b, 0.0, 255.0);
}

void Color::setAlpha(float _alpha) {
	colorData.alpha = limit(_alpha, 0.0, 255.0);
}

float Color::getR()
{
	return colorData.r;
}

float Color::getG()
{
	return colorData.g;
}

float Color::getB()
{
	return colorData.b;
}

float Color::getAlpha()
{
	return colorData.alpha;
}

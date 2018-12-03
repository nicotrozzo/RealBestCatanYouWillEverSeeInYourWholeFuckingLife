#pragma once

#include <string>
#include "allegroInit.h"

class point
{
public:
	point(unsigned int x, unsigned int y) : px(x), py(y) {}
	unsigned int getX() { return px; }
	unsigned int getY() { return py; }
private:
	unsigned int px;
	unsigned int py;
};


class rectangle
{
public:
	rectangle(point p, unsigned int h, unsigned int w) : myPoint(p), height(h), width(w) {}
	bool inRectangle(point p) { return (p.getX() >= myPoint.getX() && p.getX() <= (myPoint.getX() + width) && p.getY() >= myPoint.getY() && p.getY() <= (myPoint.getY() - width)); }
private:
	point myPoint;
	unsigned int height;
	unsigned int width;
};


class dibujator
{
public:
	dibujator();
	bool menuImageLoad();

	~dibujator();

private:
	ALLEGRO_BITMAP * menuBitmap;
	ALLEGRO_BITMAP *playBitmap;
	ALLEGRO_BITMAP *exitBitmap;
	allegroInit allInit;
};

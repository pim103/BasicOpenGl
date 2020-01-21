#include <iostream>
using namespace std;

#include "../../class/header/Point.h";

Point::Point(float newX, float newY) {
	x = newX;
	y = newY;
}

float Point::getX() {
	return x;
}

float Point::getY() {
	return y;
}
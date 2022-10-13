#include "Pad.h"

Pad::Pad(int x, int y) 
	: Actor("res/pad.png", x, y, 120, 120)
{}

float Pad::getOrientation(float clickX)
{
	return clickX - x;
}
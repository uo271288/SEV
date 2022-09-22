#pragma once
#include <string>

class Text
{
public:
	Text(std::string content, float x, float y);

	float x, y;
	int width, height;
	std::string content;
	
	void draw();
};
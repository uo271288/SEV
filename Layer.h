#pragma once

class Layer
{
public:
	virtual void init() = 0;
	virtual void processControls() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};
#pragma once

#include <unordered_set>
struct Vector2d {
	int x, y;
};

class BoundingBox
{
public:
	BoundingBox(int x, int y, int width, int height);

	void update(int x, int y);
	bool overlaps(BoundingBox& other);
	Vector2d sweep(std::unordered_set<class Actor*> actors, Vector2d& delta);

	int width, height;
	int left, right, top, bottom;
	bool touchLeft, touchRight, touchTop, touchBottom;
};
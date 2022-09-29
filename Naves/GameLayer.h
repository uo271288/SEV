#pragma once
#include "Layer.h"

#include <list>

#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Text.h"
#include "Tile.h"
#include "Space.h"

class GameLayer : public Layer
{
public:
	GameLayer();

	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;

	void loadMap(std::string name);
	void loadMapObject(char character, int x, int y);
	void calculateScroll();

	void keysToControls(SDL_Event event);

	Player* player;
	Background* background;
	Actor* backgroundPoints;
	int points;
	Text* textPoints;
	std::list<Tile*> tiles;

	std::list<Enemy*> enemies;
	std::list<Projectile*> projectiles;

	bool controlShoot = false;
	int controlMoveX = 0;
	int controlMoveY = 0;

	int newEnemyTime = 0;

	Space* space;

	float scrollX = 0;
	int mapWidth = 0;
};
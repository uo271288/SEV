#pragma once
#include "Layer.h"

#include <list>

#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Text.h"

class GameLayer : public Layer
{
public:
	GameLayer();

	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;

	void keysToControls(SDL_Event event);

	Player* player;
	Background* background;
	Actor* backgroundPoints;
	int points;
	Text* textPoints;

	std::list<Enemy*> enemies;
	std::list<Projectile*> projectiles;

	bool controlShoot = false;
	int controlMoveX = 0;
	int controlMoveY = 0;

	int newEnemyTime = 0;
};
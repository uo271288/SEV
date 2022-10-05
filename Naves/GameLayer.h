#pragma once
#include "Layer.h"

#include <list>

#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Text.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Coin.h"
#include "Bomb.h"

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

	Actor* backgroundLife;
	int life;
	Text* textLife;

	std::list<Enemy*> enemies;
	std::list<Projectile*> projectiles;
	std::list<Coin*> coins;

	bool controlShoot = false;
	int controlMoveX = 0;
	int controlMoveY = 0;

	int newEnemyTime = 0;
	int coinTime = 500;
	int bombTime = 1500;

	Bomb* bomb;
};
#pragma once

#include <unordered_set>
#include "Actor.h"

class Space
{
public:
	Space(float gravity);

	void update();

	void addDynamicActor(Actor* actor) { dynamicActors.emplace(actor); }
	void removeDynamicActor(Actor* actor) { dynamicActors.erase(actor); }

	void addStaticActor(Actor* actor) { staticActors.emplace(actor); }
	void removeStaticActor(Actor* actor) { staticActors.erase(actor); }
private:
	float gravity = 0;
	std::unordered_set<Actor*> dynamicActors;
	std::unordered_set<Actor*> staticActors;
};
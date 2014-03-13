#ifndef COLLISION_CONTROLLER_H
#define COLLISION_CONTROLLER_H

#include "_.hpp"
#include "entity.hpp"

class CollisionController {
protected:
	uint8_t count_x, count_y, step_coef;
	std::vector<std::vector<Entity*>> cells;

public:
	CollisionController();
	~CollisionController();

	void Inits(Entity* entity);
	void Updates(Entity* entity);
	void CheckCollision(Entity* entity);

	void Updates(std::vector<Entity>& entity);
};

static const int DEFAULT_STEP_COEF = 5;
static const int DEFAULT_COUNT_X = 100;
static const int DEFAULT_COUNT_Y = 100;

#endif // MAP_H

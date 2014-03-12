#ifndef LEVEL_H
#define LEVEL_H

#include "_.hpp"
#include "map.hpp"
#include "entity.hpp"
#include "entity_controller.hpp"
#include "collision_controller.hpp"

class Level {
private:
	float size_x, size_y;
	float screen_center_x, screen_center_y;

	Map map;

	std::vector<Entity> entities;
	EntityController entity_controller;

	CollisionController collision_controller;

public:
	Level(uint8_t count = 1, uint8_t index = 0, bool random_init = false);
	~Level();

	void DoStep();
	void Draw(SDL_Renderer* renderer, SDL_Texture* texture) const;

	void LoadMap(const ViewerSdl& viewer, const std::string& filename);

	void SetScreenCenter(float screen_center_x, float screen_center_y);
};

const float DEFAULT_SIZE_X = 1000.0f;
const float DEFAULT_SIZE_Y = 1000.0f;

#endif // LEVEL_H

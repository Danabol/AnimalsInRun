#ifndef MAP_H
#define MAP_H

#include "_.hpp"
#include "entity.hpp"

class Map {
private:
	std::vector<SDL_Texture*> textures;

	uint32_t count_x, count_y;
	std::vector<uint32_t> cells;

	void Clear();

public:
	Map(uint32_t count_x = 0, uint32_t count_y = 0);
	~Map();

	void Load(const ViewerSdl& viewer, const std::string& filename);
	void Draw(SDL_Renderer* renderer, const Entity& entity, float screen_center_x, float screen_center_y) const;
};

const uint8_t DEFAULT_BLOCK_SIZE = 32;

#endif // MAP_H

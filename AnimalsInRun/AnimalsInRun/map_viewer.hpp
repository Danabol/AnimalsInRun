#ifndef MAP_VIEWER_HPP
#define MAP_VIEWER_HPP

#include "_.hpp"
#include "map.hpp"
#include "entity.hpp"
#include "camera.hpp"

class MapViewer {
public:
	static const uint8_t DEFAULT_CELL_SIZE = 32;

private:
	uint32_t cell_size;
	std::vector<SDL_Texture*> textures;
	std::vector< std::vector <uint32_t> > mapVector;

public:
	MapViewer();
	~MapViewer();

	void CreateVector(Map& map);
	void Load(const ViewerSdl& viewer, const std::string& filename);
	void LoadFromFile(const std::string& filename, Map& map);
	void Draw(SDL_Renderer* renderer, const Map& map, const Entity& entity, float screen_center_x, float screen_center_y) const;
	void DrawMap(SDL_Renderer* renderer, const Map& map, Camera& camera, uint32_t size, bool squares = false) const;
	void DrawSquares(SDL_Renderer* renderer, uint8_t r, uint8_t g, uint8_t b , SDL_Rect) const;

	friend class Camera;
};

#endif // MAP_VIEWER_HPP

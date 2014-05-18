#ifndef MAP_VIEWER_HPP
#define MAP_VIEWER_HPP

#include "_.hpp"
#include "map.hpp"

class Camera
{
public:
  Camera() {
    this->camera.x = this->camera.y = 0;
    this->camera.h = this->camera.w = 320; // WARNING: Magic number.
  }
  Camera(int width, int height) {
    this->camera.x = 0;
    this->camera.y = 0;
    this->camera.w = width;
    this->camera.h = height;
  }
  Camera(const SDL_Rect& rect) {
    this->camera.x = rect.x;
    this->camera.y = rect.y;
    this->camera.w = rect.w;
    this->camera.h = rect.h;
  }
  SDL_Rect GetCamera() {
    return this->camera;
  }

private:
	SDL_Rect camera;
};

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

  void SetCellSize(uint8_t cell_size) {
    this->cell_size = cell_size;
  }

  uint32_t GetSizeX(const Map& map) const {
    return this->cell_size * map.count_x;
  }

  uint32_t GetSizeY(const Map& map) const {
    return this->cell_size * map.count_y;
  }

        void Draw(SDL_Renderer* renderer, const Map& map, uint32_t screen_size_x, uint32_t screen_size_y, float x, float y, float angle) const;


	void CreateVector(Map& map);
	void Load(const ViewerSdl& viewer, const std::string& filename);
	void LoadFromFile(const std::string& filename, Map& map);
	void DrawMap(SDL_Renderer* renderer, const Map& map, Camera& camera, uint32_t size, bool squares = false) const;
	void DrawSquares(SDL_Renderer* renderer, uint8_t r, uint8_t g, uint8_t b , SDL_Rect) const;

	friend class Camera;
};

#endif // MAP_VIEWER_HPP

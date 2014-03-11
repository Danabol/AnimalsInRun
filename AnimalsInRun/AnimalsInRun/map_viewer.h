#ifndef MAP_VIEWER_H
#define MAP_VIEWER_H

#include "_.hpp"

class MapViewer {
public:
	std::vector<SDL_Texture*> textures;

	uint32_t width, height;
	int** map;

public:
	MapViewer();
	~MapViewer();
	void LoadMap(const ViewerSdl& viewer, const std::string& filename);
	void ReleaseMap();
	void DrawMap(const ViewerSdl& viewer) const;
};

const uint8_t DEFAULT_BLOCK_SIZE = 32;

#endif // MAP_VIEWER_H
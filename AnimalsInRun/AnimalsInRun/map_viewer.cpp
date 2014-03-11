#include "map_viewer.h"

MapViewer::MapViewer() {
	this->width = 0;
	this->height = 0;
	this->map = nullptr;
}

MapViewer::~MapViewer() {
	ReleaseMap();
}

void MapViewer::ReleaseMap() {
	for each(auto texture in this->textures) {
		ViewerSdl::ReleaseTexture(texture);
	}
	if(this->map) {
		for(uint32_t i = 0; i < this->height; ++i) {
			if(this->map[i]) {
				delete[] this->map[i];
				this->map[i] = nullptr;
			}
		}
		delete[] this->map;
		this->map = nullptr;
	}
}

void MapViewer::LoadMap(const ViewerSdl& viewer, const std::string& filename)
{
	this->ReleaseMap();

	std::ifstream input(filename);
	uint32_t textures_count;
	input >> textures_count;
	std::string file_path;
	for(uint8_t i = 0; i < textures_count; ++i) {
		input >> file_path;
		this->textures.push_back(viewer.CreateTexture(file_path));
	}

	input >> this->width;
	input >> this->height;

	this->map = new int* [this->height];
	for (int i = 0; i < height; ++i) {
		this->map[i] = new int[this->width];
	}

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			input >> this->map[i][j];
			std::cout << map[i][j] << " "; // TODO: Test code. Remove.
		}
		std::cout << " " << std::endl; // TODO: Test code. Remove.
	}
}

#include "map_viewer.hpp"

MapViewer::MapViewer()
  : textures(0) {
}

MapViewer::~MapViewer() {
	for(auto it = this->textures.begin(); it < this->textures.end(); ++it) {
		ViewerSdl::ReleaseTexture(*it); // TODO: Check.
	}
	this->textures.clear();
}

void MapViewer::Draw(SDL_Renderer* renderer, const Map& map, uint32_t screen_size_x, uint32_t screen_size_y, float x, float y, float angle) const {
	if(renderer) {
	  uint8_t r = 0; // TODO: Add to resorces.
	  uint8_t g = 0; // TODO: Add to resorces.
	  uint8_t b = 255; // TODO: Add to resorces.
	  uint8_t a = 0; // TODO: Add to resorces.

		float px, py;
		auto it = map.cells.begin();
		py = 0.0f;
		for (uint32_t iy = 0; iy < map.count_y; ++iy) {
			px = 0.0f;
			for (uint32_t ix = 0; ix < map.count_x; ++ix) {
				if(*it) {
				  SDL_SetRenderDrawColor(renderer, r, g, b, a);
					SDL_Rect rect;
					rect.x = (screen_size_x >> 1) + (int)(px - x);
					rect.y = (screen_size_y >> 1) + (int)(py - y);
					rect.w = rect.h = cell_size;
					SDL_RenderFillRect(renderer, &rect);

				}
				++it;
				px += cell_size;
			}
			py += cell_size;
		}
	}
}

void MapViewer::CreateVector(Map& map)
{
	std::vector< std::vector <uint32_t> > vectFull(map.count_y);

	std::vector<uint32_t> vect(map.count_x);
	for (int i = 0; i < map.cells.size(); i++)
	{
		if(vect.size() == map.count_x)
		{
			vectFull.push_back(vect);
			vect.clear();
		}
		else
		{
			vect.push_back(map.cells[i]);
		}
	}

	this->mapVector = vectFull;

}

void MapViewer::LoadFromFile( const std::string& filename, Map& map)
{
	int width, height, current;


    std::ifstream input(filename);

	input>>width ;//width
	input>>height;//height
	std::vector<std::vector<uint32_t>>gameMap(width);

	//map.SetXCount(width);
	//map.SetYCount(height);


	for(int i = 0;i < height; i++)//height
	{
		std::vector<uint32_t> vect(width);
		for(int j = 0; j < width; j++)//width
		{
			input>>current;
			if(current>=0 && current<=9)
			{
				vect.push_back(current);
			}
		/*	else
			{
				vect.push_back(0);
			}*/
		}
		gameMap.push_back(vect);
	}
	input.close();

//	map.SetMap(gameMap);

}

void MapViewer::DrawMap(SDL_Renderer* renderer, const Map& map, Camera& cam, uint32_t size, bool squares) const
{
	SDL_Rect rect = cam.GetCamera();
	uint32_t squareX = (rect.w - rect.x)/ size;
	uint32_t squareY = (rect.h - rect.y)/ size;
	uint32_t posX = rect.x/size;
	uint32_t posY = rect.y/size;

	if(renderer)
	{
		for (uint32_t i = posX; i <= (squareX + posX); i++)
		{
			for (uint32_t j = posY; j <= (squareY + posY); j++)
			{
				SDL_Rect rectangleForDraw;
				rectangleForDraw.x = i * size;
				rectangleForDraw.y = j * size;
				rectangleForDraw.h = rectangleForDraw.w = size;

				if(!squares)
				{
					SDL_RenderCopy(renderer, textures[0], NULL, &rect); //Копируем в рендер персонажа
				}
				else
				{
					DrawSquares(renderer,0,0,0,rectangleForDraw);
				}
			}
		}
	}
}

void MapViewer::DrawSquares(SDL_Renderer* renderer, uint8_t r, uint8_t g, uint8_t b , SDL_Rect rect) const
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 0);
	SDL_RenderFillRect(renderer, &rect);
}

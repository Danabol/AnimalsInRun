#include "map_viewer.hpp"

#include "entity_viewer.hpp"

MapViewer::MapViewer()
  : textures(0) {
}

MapViewer::~MapViewer() {
	for(auto it = this->textures.begin(); it < this->textures.end(); ++it) {
		ViewerSdl::ReleaseTexture(*it); // TODO: Check.
	}
	this->textures.clear();
}

//void MapViewer::Draw(SDL_Renderer* renderer, const Map& map, const Entity& entity, float screen_center_x, float screen_center_y) const {
//	if(renderer) {
//		EntityViewer block;
//		block.angle = -entity.angle;
//		block.r = DEFAULT_CELL_SIZE >> 1;
//
//		float angle_rad = entity.angle * TO_RAD;
//		float sin_angle_rad = std::sin(angle_rad);
//		float cos_angle_rad = std::cos(angle_rad);
//
//		float px = 0.0f;
//		float py = 0.0f;
//		auto it = map.cells.begin();
//		for (uint32_t i = 0; i < map.count_x; ++i) {
//			for (uint32_t j = 0; j < map.count_y; ++j) {
//				if(*it) {
//					float x = px - entity.px;
//					float y = py - entity.py;
//					block.px = screen_center_x + sin_angle_rad * x - cos_angle_rad * y;
//					block.py = screen_center_y + cos_angle_rad * x + sin_angle_rad * y;
//					if(*it - 1 < this->textures.size()) {
//						block.Draw(renderer, 0, 0, 255);
//					}
//					else {
//						block.Draw(renderer, this->textures[*it - 1]);
//					}
//				}
//				++it;
//				py += DEFAULT_CELL_SIZE;
//			}
//			px += DEFAULT_CELL_SIZE;
//			py = 0.0f;
//		}
//	}
//}

void MapViewer::Draw(SDL_Renderer* renderer, const Map& map, const Entity& entity, float screen_center_x, float screen_center_y) const {
	if(renderer) {
		EntityViewer block;
		block.angle = -entity.angle;
		block.r = DEFAULT_CELL_SIZE >> 1;

		float px = 0.0f;
		float py = 0.0f;
		auto it = map.cells.begin();
		for (uint32_t i = 0; i < map.count_x; ++i) {
			for (uint32_t j = 0; j < map.count_y; ++j) {
				if(*it) {
					float x = px - entity.px;
					float y = py - entity.py;
					block.px = screen_center_x + x;
					block.py = screen_center_y + y;
					if(*it - 1 >= this->textures.size()) {
						block.Draw(renderer, 0, 0, 255);
					}
					else {
						block.Draw(renderer, this->textures[*it]);
					}
				}
				++it;
				py += DEFAULT_CELL_SIZE;
			}
			px += DEFAULT_CELL_SIZE;
			py = 0.0f;
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

void MapViewer::DrawMap(SDL_Renderer* renderer, const Map& map, Camera& cam, uint32_t size, bool squares = false) const
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



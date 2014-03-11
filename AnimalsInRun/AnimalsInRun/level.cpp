#include "level.hpp"

Level::Level(uint8_t count, uint8_t index, bool random_init)
	: size_x(DEFAULT_SIZE_X), size_y(DEFAULT_SIZE_Y), screen_center_x(0.5f * DEFAULT_SIZE_X), screen_center_y(0.5f * DEFAULT_SIZE_Y) {

		this->heroes.resize(count);
		this->index = index;
		if(random_init) {
			for(auto it = this->heroes.begin(); it < this->heroes.end(); ++it) {
				it->angle = static_cast<float>(rand() % 360);
				it->px = 1.0f * rand() / RAND_MAX * this->size_x;
				it->py = 1.0f * rand() / RAND_MAX * this->size_y;
				this->map.Inits(static_cast<Entity*>(it._Ptr));
			}
		}
}

Level::~Level() {
}

void Level::DoStep() {
	for(size_t i = 0; i < this->heroes.size(); ++i) {
		if(i == this->index) {
			this->heroes[i].Hero::DoStep();
		}
		else {
			this->heroes[i].Entity::DoStep();
		}

		//if(this->heroes[i].px < 0 || this->size_x < this->heroes[i].px || this->heroes[i].py < 0 || this->size_y < this->heroes[i].py) {
		//	this->heroes[i].angle = rand() % 360;
		//	this->heroes[i].px = 1.0f * rand() / RAND_MAX * this->size_x;
		//	this->heroes[i].py = 1.0f * rand() / RAND_MAX * this->size_y;
		//}

		this->map.Updates(&(this->heroes[i]));
	}

	//for(size_t i = 0; i < this->heroes.size() - 1; ++i) {
	//	for(size_t j = i + 1; j < this->heroes.size(); ++j) {
	//		collision(this->heroes[i], this->heroes[j]);
	//	}
	//}

	for(int i = 0; i < this->heroes.size(); ++i) {
		this->map.CheckCollision(&(this->heroes[i]));
	}

	for(int i = 0; i < this->heroes.size(); ++i) {
		this->map.Updates(&(this->heroes[i]));
	}
}

void Level::Draw(SDL_Renderer* renderer, SDL_Texture* texture) const {
	if(renderer) {
		const Hero& hero_current = this->heroes[this->index];
		Hero hero;
		if(this->map_viewer.map) {
			for (int i = 0; i < this->map_viewer.height; i++) {
				for (int j = 0; j < this->map_viewer.width; j++) {
					if(this->map_viewer.map[i][j]) {
						hero.px = i * DEFAULT_BLOCK_SIZE;
						hero.py = j * DEFAULT_BLOCK_SIZE;
						hero.angle = 0;
						float x = hero.px - hero_current.px;
						float y = hero.py - hero_current.py;
						float angle_rad = hero_current.angle * TO_RAD;
						hero.px = std::sin(angle_rad) * x - std::cos(angle_rad) * y;
						hero.py = std::cos(angle_rad) * x + std::sin(angle_rad) * y;
						hero.px += this->screen_center_x;
						hero.py += this->screen_center_y;
						hero.angle -= hero_current.angle;
						hero.Draw(renderer, this->map_viewer.textures[this->map_viewer.map[i][j] - 1]);
					}
				}
			}
		}

		for(size_t i = 0; i < this->heroes.size(); ++i) {
			hero = this->heroes[i];
			float x = hero.px - hero_current.px;
			float y = hero.py - hero_current.py;
			float angle_rad = hero_current.angle * TO_RAD;
			hero.px = std::sin(angle_rad) * x - std::cos(angle_rad) * y;
			hero.py = std::cos(angle_rad) * x + std::sin(angle_rad) * y;
			hero.px += this->screen_center_x;
			hero.py += this->screen_center_y;
			hero.angle -= hero_current.angle;
			hero.Draw(renderer, texture);
		}
	}
}

void Level::LoadMap(const ViewerSdl& viewer, const std::string& filename) {
	this->map_viewer.LoadMap(viewer, filename);
}

void Level::SetScreenCenter(float screen_center_x, float screen_center_y) {
	this->screen_center_x = screen_center_x;
	this->screen_center_y = screen_center_y;
}

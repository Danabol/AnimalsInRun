#include "level.hpp"

#include "entity_viewer.hpp"

Level::Level(uint8_t count, uint8_t index, bool random_init)
	: size_x(DEFAULT_SIZE_X), size_y(DEFAULT_SIZE_Y), screen_center_x(0.5f * DEFAULT_SIZE_X), screen_center_y(0.5f * DEFAULT_SIZE_Y) {

		this->entities.resize(count);
		if(random_init) {
			for(auto it = this->entities.begin(); it < this->entities.end(); ++it) {
				it->angle = static_cast<float>(rand() % 360);
				it->px = 1.0f * rand() / RAND_MAX * this->size_x;
				it->py = 1.0f * rand() / RAND_MAX * this->size_y;

				this->collision_controller.Inits(static_cast<Entity*>(&it[0]));
			}
		}
		if(index < this->entities.size()) {
			this->entity_controller.entity = &this->entities[index];
		}
}

Level::~Level() {
}

void Level::DoStep() {
	this->entity_controller.DoStep();
	for(auto it = this->entities.begin(); it < this->entities.end(); ++it) {
		it->DoStep();

		this->collision_controller.Updates(&(*it));

		//if(this->entities[i].px < 0 || this->size_x < this->entities[i].px || this->entities[i].py < 0 || this->size_y < this->entities[i].py) {
		//	this->entities[i].angle = rand() % 360;
		//	this->entities[i].px = 1.0f * rand() / RAND_MAX * this->size_x;
		//	this->entities[i].py = 1.0f * rand() / RAND_MAX * this->size_y;
		//}
	}

	//for(size_t i = 0; i < this->entities.size() - 1; ++i) {
	//	for(size_t j = i + 1; j < this->entities.size(); ++j) {
	//		collision(this->entities[i], this->entities[j]);
	//	}
	//}

	for(auto it = this->entities.begin(); it < this->entities.end(); ++it) {
		this->collision_controller.CheckCollision(&(*it));
	}
	// TODO: this->collision_controller.Updates(this->entities);
}

void Level::Draw(SDL_Renderer* renderer, SDL_Texture* texture) const {
	if(renderer) {
		const Entity* entity = this->entity_controller.entity;
		if(entity) {
			this->map.Draw(renderer, *entity, this->screen_center_x, this->screen_center_y);

			float angle_rad = entity->angle * TO_RAD;
			float sin_angle_rad = std::sin(angle_rad);
			float cos_angle_rad = std::cos(angle_rad);

			EntityViewer entity_viewer;
			for(auto it = this->entities.begin(); it < this->entities.end(); ++it) {
				entity_viewer.r = it->r;
				float x = it->px - entity->px;
				float y = it->py - entity->py;;
				entity_viewer.px = this->screen_center_x + sin_angle_rad * x - cos_angle_rad * y;
				entity_viewer.py = this->screen_center_y + cos_angle_rad * x + sin_angle_rad * y;
				entity_viewer.angle = it->angle - entity->angle;
				entity_viewer.Draw(renderer, texture);
			}
		}
	}
}

void Level::LoadMap(const ViewerSdl& viewer, const std::string& filename) {
	this->map.Load(viewer, filename);
}

void Level::SetScreenCenter(float screen_center_x, float screen_center_y) {
	this->screen_center_x = screen_center_x;
	this->screen_center_y = screen_center_y;
}

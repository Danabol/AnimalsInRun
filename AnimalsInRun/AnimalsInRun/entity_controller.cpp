#include "entity_controller.hpp"

void EntityController::DoStep() const{
	if(this->Entity) {
		const uint8_t *keys = SDL_GetKeyboardState(NULL);
		float coef = keys[SDL_SCANCODE_DOWN] | keys[SDL_SCANCODE_UP]? 0.5f : 1.0f;
		this->Entity->angle += coef * DEFAULT_ANGLE_STEP * (keys[SDL_SCANCODE_RIGHT] - keys[SDL_SCANCODE_LEFT]);
		this->Entity->speed = DEFAULT_SPEED * (keys[SDL_SCANCODE_DOWN] - keys[SDL_SCANCODE_UP]);
		this->Entity->vx = std::cos(this->Entity->angle * TO_RAD) * this->Entity->speed;
		this->Entity->vy = std::sin(this->Entity->angle * TO_RAD) * this->Entity->speed;
		this->Entity->px += this->Entity->vx;
		this->Entity->py += this->Entity->vy;
	}
}

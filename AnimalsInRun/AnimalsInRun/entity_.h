#ifndef ENTITY__H
#define ENTITY__H

#include "_.hpp"

const uint8_t MAX_ACTION_COUNT = 10;

class Entity_ {
public:
	Texture* texture;

	int16_t i, j;
	int8_t angle_index;
	int8_t angle_step; // Need min_angle, max_angle.

	uint8_t actions[MAX_ACTION_COUNT];
	uint8_t action_count;

	// TODO: uint8_t type;
	// TODO: uint8_t points;
	// TODO: Boost* currentBoost;

public:
	Entity_();
	~Entity_();

	void DoStep(uint8_t action_index);
};

#endif // ENTITY__H
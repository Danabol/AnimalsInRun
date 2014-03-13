#ifndef ENTITY_CONTROLLER_H
#define ENTITY_CONTROLLER_H

#include "entity.hpp"

class EntityController {
public:
	Entity* entity;

public:
	EntityController();

	void DoStep() const;
};

#endif // ENTITY_CONTROLLER_H

#include "../includes/physicsCore.h"

void PhysicsWorld::addObject(PhyObject* object)
{
	phyObjects.push_back(object);
}

void PhysicsWorld::removeObject(PhyObject* object)
{
	std::vector<PhyObject*>::iterator it = find(phyObjects.begin(), phyObjects.end(), object);

	if (it != phyObjects.end())
		phyObjects.erase(it);
}

void PhysicsWorld::step(float dt)
{
	for (PhyObject* obj : phyObjects)
	{
		obj->force = obj->force + (gravity * obj->mass);

		obj->velocity = obj->velocity + (obj->force / obj->mass * dt);
		obj->position = obj->position + (obj->velocity * dt);

		obj->force = { 0.0f };
	}
}
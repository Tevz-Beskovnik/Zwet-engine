#pragma once
#include<vector>
#include"vecs.h"
#include<iostream>

typedef struct PhyObject{
	vecs::vec3 position = { 0.0f };
	vecs::vec3 velocity = { 0.0f };
	vecs::vec3 force = { 0.0f };
	float mass;
} PhyObject;

class PhysicsWorld
{
	public:
		//add physics object
		void addObject(PhyObject* object);

		//remove physics object
		void removeObject(PhyObject* object);

		//step function for physics world (dt -> delta time)
		void step(float dt);

	private:
		vecs::vec3 gravity = { 0.0f, -9.81f, 0.0f };
		std::vector<PhyObject*> phyObjects;
};
#pragma once
#include <vector>
#include "Particle.h"

class ParticleSystem
{
public:

#define POOL_SIZE 1000 // Max 1000 particles

	std::vector<Particle> _pool;
	ParticleSystem();
	void Main();
	void Start();
	void Update();
};
#include "ParticleSystem.h"
#include "raylib.h"
#include "Particle.h"
#include <iostream>

ParticleSystem::ParticleSystem()
{

}

Color RandomColor()
{
	return Color{ (unsigned char)GetRandomValue(0,255),(unsigned char)GetRandomValue(0,255),(unsigned char)GetRandomValue(0,255),255 };
}

void ParticleSystem::Main()
{
	Start();

	InitWindow(800, 800, "RayGame");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(Color{ 20,20,20,255 });

		BeginBlendMode(BLEND_ADDITIVE);

		Update();

		EndBlendMode();

		EndDrawing();
	}

	CloseWindow();
}

void ParticleSystem::Start()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		_pool.emplace_back();
	}
}

void ParticleSystem::Update()
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		int rate = GetRandomValue(3, 20);

		for (int r = 0; r < rate; r++)
		{
			auto it = find_if(_pool.begin(), _pool.end(), [](Particle& c) {return !c._active; });
			if (it != _pool.end())
			{
				it->Activate(GetMousePosition(), (float)GetRandomValue(5, 50), RandomColor(), (float)GetRandomValue(2, 8), (float)GetRandomValue(0, 360));
			}
		}
	}

	for (int i = 0; i < _pool.size(); i++)
	{
		_pool[i].Update();
		_pool[i].Draw();
	}
}
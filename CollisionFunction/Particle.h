#pragma once
#include "raylib.h"

class Particle
{
public:
	Vector2 _center{ 0,0 };
	float _radius = 0;
	Color _color = BLACK;
	float _speed = 0;
	float _angle = 20;
	const float _gravity = 10;
	bool _active = false;

	void Activate(Vector2 center, float radius, Color color, float speed, float angle);
	void Draw();
	void Update();
};
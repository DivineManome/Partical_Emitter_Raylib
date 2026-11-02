#include "Particle.h"
#include "raylib.h"
#include <cmath>

void Particle::Activate(Vector2 center, float radius, Color color, float speed, float angle)
{
	this->_center = center;
	this->_radius = radius;
	this->_color = color;
	this->_speed = speed;
	this->_angle = angle;
	_active = true;
}

void Particle::Draw()
{
	if (_active) { DrawCircleV(_center, _radius, _color); }
}

void Particle::Update()
{
	if (!this->_active) return;

	_center.y += sin(_angle * DEG2RAD) * _speed + _gravity;
	_center.x += cos(_angle * DEG2RAD) * _speed;
	_radius += 0.1;


	float alpha = _color.a;

	alpha -= 10;
	_color.a = alpha;

	if (alpha < 0)
	{
		_active = false;
	}
}

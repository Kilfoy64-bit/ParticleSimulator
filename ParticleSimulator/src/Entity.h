#pragma once

#include "Renderer.h"

struct Coordinates {
	float x;
	float y;
};

enum class Direction {
	Up,
	Down,
	Left,
	Right
};

class Entity {
protected:
	Renderer m_Renderer;
	Coordinates m_Center;
public:
	Entity(Renderer &renderer) 
		: m_Renderer(renderer), m_Center{0.0f, 0.0f} {};
	Entity(Renderer &renderer, Coordinates center)
		: m_Renderer(renderer), m_Center{center} {};
	~Entity() {};

	inline virtual void Render(Shader& shader) const { 0; }
	inline virtual void Move(Direction direction) { 0; }
};
#pragma once

#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Point {
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
	Point m_Center;
	
	glm::mat4 projectionMatrix = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);

public:
	Entity() 
		: m_Center{0.0f, 0.0f} {};
	Entity(Point center)
		: m_Center{center} {};
	~Entity() {};

	inline virtual void Render(Renderer &renderer, Shader& shader) const { 0; }
	inline virtual void Move(Direction direction) { 0; }
};
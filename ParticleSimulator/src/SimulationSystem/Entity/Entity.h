#pragma once

#include "../GraphicsEngine/Renderer/Renderer.h"

#include "../PhysicsEngine/Point2D/Point2D.h"
#include "../GraphicsEngine/VertexArray/VertexArray.h"
#include "../GraphicsEngine/VertexBuffer/VertexBuffer.h"
#include "../GraphicsEngine/VertexBuffer/VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


enum class Direction {
	Stationary,
	Up,
	Down,
	Left,
	Right
};

class Entity {
protected:
	Point2D m_Position;
	glm::mat4 projectionMatrix = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
	
	VertexArray m_VertexArray;
	VertexBuffer m_VertexBuffer;
	VertexBufferLayout m_VertexBufferlayout;
	IndexBuffer m_IndexBuffer;

	std::vector<float> m_Positions;
	std::vector<unsigned int> m_Indices;
	std::vector<float> m_Color = { 0.0f, 0.0f, 0.0f, 0.0f };
	
	inline virtual void moveDirection(Direction direction) { 0; };

public:
	Entity() 
		: m_Position{0.0f, 0.0f} {};
	Entity(Point2D position)
		: m_Position{ position } {};
	~Entity() {};

	inline virtual void render(Renderer &renderer, Shader& shader) const { 0; }
	inline virtual void update(long deltaTime) { 0; }
	//inline virtual bool checkEntityCollision(Entity other) { 0; }
};
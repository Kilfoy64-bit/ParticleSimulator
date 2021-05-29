#include "Particle.h"

#include <math.h>
#include <vector>

void Particle::CalculatePosition()
{
	m_Positions = {};

	// Center 0 
	m_Positions.push_back(m_Center.x);
	m_Positions.push_back(m_Center.y);
	m_Positions.push_back(0.0f);
	m_Positions.push_back(0.0f);

	// Directly above circle 1
	m_Positions.push_back(m_Center.x);
	m_Positions.push_back(m_Center.y - m_Radius);
	m_Positions.push_back(0.0f);
	m_Positions.push_back(0.0f);
	
	for (int i = 0; i <= m_Steps; i++) {
		float newX = m_Radius * sin(m_Beta * i);
		float newY = m_Radius * cos(m_Beta * i);

		m_Positions.push_back(m_Center.x + newX);
		m_Positions.push_back(m_Center.y + newY);
		m_Positions.push_back(0.0f);
		m_Positions.push_back(0.0f);
	}

}

Point Particle::CalculateNewCenter(Direction direction)
{
	Point newCenter = { m_Center.x, m_Center.y };
	switch (direction)
	{
	case Direction::Up:
		newCenter = { m_Center.x, m_Center.y + m_Speed };
		break;
	case Direction::Right:
		newCenter = { m_Center.x + m_Speed, m_Center.y };
		break;
	case Direction::Down:
		newCenter = { m_Center.x, m_Center.y - m_Speed };
		break;
	case Direction::Left:
		newCenter = { m_Center.x - m_Speed, m_Center.y };
		break;
	}
	return newCenter;
}

Particle::Particle(Point center, float radius)
	: Entity(center), m_Radius(radius)
{
	for (int i = 0; i <= m_Steps; i++) {
		m_Indices.push_back(0);
		m_Indices.push_back(i+1);
		m_Indices.push_back(i+2);
	}

	CalculatePosition();

	m_IndexBuffer.Update(&m_Indices[0], m_Indices.size());
	m_VertexBuffer.Update(&m_Positions[0], m_Positions.size() * sizeof(float));

	m_VertexBufferlayout.Push<float>(2);
	m_VertexBufferlayout.Push<float>(2);

	m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexBufferlayout);

	m_VertexArray.Unbind();
	m_VertexBuffer.Unbind();
	m_IndexBuffer.Unbind();
}

Particle::~Particle()
{
}

void Particle::Render(Renderer& renderer, Shader& shader) const
{
	shader.Bind();
	shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	shader.SetUniformMat4f("u_MVP", projectionMatrix);
	shader.Unbind();

	renderer.Draw(m_VertexArray, m_IndexBuffer, shader);
}

void Particle::Move(Direction direction)
{
	m_Center = CalculateNewCenter(direction);
	CalculatePosition();
	m_VertexBuffer.Update(&m_Positions[0], m_Positions.size() * sizeof(float));
}

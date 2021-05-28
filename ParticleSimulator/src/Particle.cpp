#include "Particle.h"

#include <math.h>
#include <vector>

float* Particle::CalculatePosition()
{
	m_Positions = {};

	float prevX = m_Center.x;
	float prevY = m_Center.y - m_Radius;
	
	for (int i = 0; i <= m_Steps; i++) {
		float newX = m_Radius * sin(m_Beta * i);
		float newY = m_Radius * cos(m_Beta * i);

		m_Positions.push_back(m_Center.x);
		m_Positions.push_back(m_Center.y);
		m_Positions.push_back(0.0f);

		m_Positions.push_back(prevX);
		m_Positions.push_back(prevY);
		m_Positions.push_back(0.0f);

		m_Positions.push_back(newX);
		m_Positions.push_back(newY);
		m_Positions.push_back(0.0f);

		prevX = newX;
		prevY = newY;
	}

	return &m_Positions[0];
}

Point Particle::CalculateNewCenter(Direction direction)
{
	return Point();
}

Particle::Particle(Point center, float radius)
	: Entity(center), m_Radius(radius)
{
	for (int i = 0; i <= m_Steps; i++) {
		m_Indices.push_back(0);
		m_Indices.push_back(i+1);
		m_Indices.push_back(i+2);
	}

	float* positions = CalculatePosition();

	m_IndexBuffer.Update(&m_Indices[0], ((m_Steps + 1) * 3));
	m_VertexBuffer.Update(positions, m_Positions.size() * 3 * sizeof(float));

	for (int i = 0; i <= m_Steps; i++) {
		m_VertexBufferlayout.Push<float>(1);
	}

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
}

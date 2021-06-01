#include "Particle.h"

#include "RandomNumberGenerator.h"

#include <math.h>

void Particle::updateBuffers()
{
	m_IndexBuffer.update(&m_Indices[0], m_Indices.size());
	m_VertexBuffer.update(&m_Positions[0], m_Positions.size() * sizeof(float));

	m_VertexBufferlayout.Push<float>(2);

	m_VertexArray.addBuffer(m_VertexBuffer, m_VertexBufferlayout);

	m_VertexArray.unbind();
	m_VertexBuffer.unbind();
	m_IndexBuffer.unbind();
}

void Particle::calculatePosition()
{
	m_Positions = {};

	// Center 0 
	m_Positions.push_back(m_Position.x);
	m_Positions.push_back(m_Position.y);

	// Directly above circle 1
	m_Positions.push_back(m_Position.x);
	m_Positions.push_back(m_Position.y - m_Radius);

	for (unsigned int i = 0; i <= m_Vertices; i++) {
		float newX = m_Radius * sin(m_Beta * i);
		float newY = m_Radius * cos(m_Beta * i);

		m_Positions.push_back(m_Position.x + newX);
		m_Positions.push_back(m_Position.y + newY);
	}
}

void Particle::move(long deltaTime)
{
	m_Position = { m_Position.x + (m_Velocity.getX() * deltaTime) , m_Position.y + (m_Velocity.getY() * deltaTime) };
	calculatePosition();
}

void Particle::resolveContainerCollision()
{
	if ((m_Position.x - m_Radius) <= m_Container.getLeft()) {
		float x = m_Velocity.getX() < 0 ? abs(m_Velocity.getX()) : m_Velocity.getX();
		m_Velocity.setComponents(x, m_Velocity.getY());
	}	
	else if ((m_Position.x + m_Radius) >= m_Container.getRight()) {
		float x = m_Velocity.getX() < 0 ? m_Velocity.getX() : -1 * m_Velocity.getX();
		m_Velocity.setComponents(x, m_Velocity.getY());
	}
	else if ((m_Position.y - m_Radius) <= m_Container.getBottom()) {
		float y = m_Velocity.getY() < 0 ? abs(m_Velocity.getY()) : m_Velocity.getY();
		m_Velocity.setComponents(m_Velocity.getX(), y);
	}
	else if ((m_Position.y + m_Radius) >= m_Container.getTop()) {
		float y = m_Velocity.getY() < 0 ? m_Velocity.getY() : -1 * m_Velocity.getY();
		m_Velocity.setComponents(m_Velocity.getX(), y);
	}
}

bool Particle::detectParticleCollision(Particle other)
{
	float centerPointDistance = m_Position.distance(other.getPosition());

	if (centerPointDistance <= (m_Radius + other.getRadius())) {
		return true;
	}
	else {
		return false;
	}
}

Particle::Particle(Point2D center, Box &container)
	: Entity(center), m_Velocity(Vector2D()), m_Container(container)
{
	auto& rng = RandomNumberGenerator::Get();
	setColor(rng.FloatVec(0.1f, 1.0f, 4));
	setRadius(rng.Float(10.0f, 100.0f));
	setSpeed((100.0f/m_Radius) * 0.5f);
	m_Velocity.setMagnitude(m_Speed);
	m_Velocity.setTheta(rng.Double(0.0, 2.0 * PI));

	for (unsigned int i = 0; i <= m_Vertices; i++) {
		m_Indices.push_back(0);
		m_Indices.push_back(i+1);
		m_Indices.push_back(i+2);
	}

	calculatePosition();
	updateBuffers();
}

Particle::~Particle()
{
}

void Particle::render(Renderer& renderer, Shader& shader) const
{
	shader.bind();
	shader.setUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
	shader.setUniformMat4f("u_MVP", projectionMatrix);
	shader.unbind();

	renderer.draw(m_VertexArray, m_IndexBuffer, shader);
}

void Particle::update(long deltaTime)
{
	/*std::cout << "X: " << m_Velocity.getX() << std::endl;
	std::cout << "Y: " << m_Velocity.getY() << std::endl;
	std::cout << "Theta: " << m_Velocity.getTheta() << std::endl;
	std::cout << "Magnitude: " << m_Velocity.getMagnitude() << std::endl;*/
	
	move(deltaTime);
	//moveDirection(Direction::Right);
	resolveContainerCollision();

	m_VertexBuffer.update(&m_Positions[0], m_Positions.size() * sizeof(float));
}
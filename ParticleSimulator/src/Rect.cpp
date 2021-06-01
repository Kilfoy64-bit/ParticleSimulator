#include "Rect.h"

void Rect::updateBuffers()
{
    m_IndexBuffer.update(&m_Indices[0], m_Indices.size());
    m_VertexBuffer.update(&m_Positions[0], m_Positions.size() * sizeof(float));

    m_VertexBufferlayout.Push<float>(2);

    m_VertexArray.addBuffer(m_VertexBuffer, m_VertexBufferlayout);

    m_VertexArray.unbind();
    m_VertexBuffer.unbind();
    m_IndexBuffer.unbind();
}

void Rect::calculatePosition()
{
    m_Positions = {
            m_Position.x - (0.5f * m_Width), m_Position.y - (0.5f * m_Height), // 0
            m_Position.x + (0.5f * m_Width), m_Position.y - (0.5f * m_Height), // 1
            m_Position.x + (0.5f * m_Width), m_Position.y + (0.5f * m_Height), // 2
            m_Position.x - (0.5f * m_Width), m_Position.y + (0.5f * m_Height)  // 3
    };
}

void Rect::moveDirection(Direction direction)
{
    switch (direction)
    {
    case Direction::Up:
        m_Position = { m_Position.x, m_Position.y + m_Speed };
        break;
    case Direction::Right:
        m_Position = { m_Position.x + m_Speed, m_Position.y };
        break;
    case Direction::Down:
        m_Position = { m_Position.x, m_Position.y - m_Speed };
        break;
    case Direction::Left:
        m_Position = { m_Position.x - m_Speed, m_Position.y };
        break;
    }
    calculatePosition();
}

Rect::Rect(Point2D center, float side)
    : Entity(center), m_Width(side), m_Height(side)
{
    calculatePosition();
    updateBuffers();
}

Rect::Rect(Point2D center, float width, float height)
    : Entity(center), m_Width(width), m_Height(height)
{
    calculatePosition();
    updateBuffers();
}

Rect::~Rect()
{
    m_VertexArray.unbind();
    m_VertexBuffer.unbind();
    m_IndexBuffer.unbind();
}

void Rect::render(Renderer& renderer, Shader& shader) const
{
    shader.bind();
    shader.setUniform4f("u_Color", 0.0f, 0.3f, 1.0f, 1.0f);
    shader.setUniformMat4f("u_MVP", projectionMatrix);
    shader.unbind();

    renderer.draw(m_VertexArray, m_IndexBuffer, shader);
}

void Rect::update(long deltaTime)
{
    moveDirection(m_Direction);
    m_VertexBuffer.update(&m_Positions[0], m_Positions.size() * sizeof(float));
}
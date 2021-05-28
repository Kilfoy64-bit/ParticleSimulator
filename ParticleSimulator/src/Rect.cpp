#include "Rect.h"

float* Rect::CalculatePosition()
{
    m_Positions = {
            m_Center.x - (0.5f * m_Width), m_Center.y - (0.5f * m_Height), 0.0f, 0.0f, // 0
            m_Center.x + (0.5f * m_Width), m_Center.y - (0.5f * m_Height), 1.0f, 0.0f, // 1
            m_Center.x + (0.5f * m_Width), m_Center.y + (0.5f * m_Height), 1.0f, 1.0f, // 2
            m_Center.x - (0.5f * m_Width), m_Center.y + (0.5f * m_Height), 0.0f, 1.0f  // 3
    };
    return &m_Positions[0];
};

Point Rect::CalculateNewCenter(Direction direction)
{
    Point newCenter = { m_Center.x, m_Center.y };
    switch (direction)
    {
    
    case Direction::Up:
        newCenter = { m_Center.x, m_Center.y + m_Speed};
        break;
    case Direction::Right:
        newCenter = { m_Center.x + m_Speed, m_Center.y};
        break;
    case Direction::Down:
        newCenter = { m_Center.x, m_Center.y - m_Speed };
        break;
    case Direction::Left:
        newCenter = { m_Center.x - m_Speed, m_Center.y};
        break;
    }
    return newCenter;
};

Rect::Rect(Point center, float side)
    : Entity(center), m_Width(side), m_Height(side)
{
    float* positions = CalculatePosition();

    m_IndexBuffer.Update(m_Indices, 6);
    
    m_VertexBuffer.Update(positions, 4 * 4 * sizeof(float));
    m_VertexBufferlayout.Push<float>(2);
    m_VertexBufferlayout.Push<float>(2);
    m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexBufferlayout);

    m_VertexArray.Unbind();
    m_VertexBuffer.Unbind();
    m_IndexBuffer.Unbind();
};

Rect::Rect(Point center, float width, float height)
    : Entity(center), m_Width(width), m_Height(height)
{
    float* positions = CalculatePosition();

    m_IndexBuffer.Update(m_Indices, 6);

    m_VertexBuffer.Update(positions, 4 * 4 * sizeof(float));
    m_VertexBufferlayout.Push<float>(2);
    m_VertexBufferlayout.Push<float>(2);
    m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexBufferlayout);

    m_VertexArray.Unbind();
    m_VertexBuffer.Unbind();
    m_IndexBuffer.Unbind();
}

Rect::~Rect()
{
    m_VertexArray.Unbind();
    m_VertexBuffer.Unbind();
    m_IndexBuffer.Unbind();
};

void Rect::Render(Renderer& renderer, Shader& shader) const
{
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.0f, 0.3f, 1.0f, 1.0f);
    shader.SetUniformMat4f("u_MVP", projectionMatrix);
    shader.Unbind();

    renderer.Draw(m_VertexArray, m_IndexBuffer, shader);
};

void Rect::Move(Direction direction)
{
    m_Center = CalculateNewCenter(direction);
    float* positions = CalculatePosition();
    m_VertexBuffer.Update(positions, 4 * 4 * sizeof(float));
}
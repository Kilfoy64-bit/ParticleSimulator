#include "Rect.h"

float* Rect::CalculatePosition()
{
    float positions[16] = {
            m_Center.x - (0.5f * m_Width), m_Center.y - (0.5f * m_Height), 0.0f, 0.0f, // 0
            m_Center.x + (0.5f * m_Width), m_Center.y - (0.5f * m_Height), 1.0f, 0.0f, // 1
            m_Center.x + (0.5f * m_Width), m_Center.y + (0.5f * m_Height), 1.0f, 1.0f, // 2
            m_Center.x - (0.5f * m_Width), m_Center.y + (0.5f * m_Height), 0.0f, 1.0f  // 3
    };
    return positions;
};

Coordinates Rect::CalculateNewCenter(Direction direction)
{
    Coordinates newCenter = { m_Center.x, m_Center.y };
    switch (direction)
    {
    
    case Direction::Up:
        newCenter = { m_Center.x, m_Center.y + SPEED};
        break;
    case Direction::Right:
        newCenter = { m_Center.x + SPEED, m_Center.y};
        break;
    case Direction::Down:
        newCenter = { m_Center.x, m_Center.y - SPEED};
        break;
    case Direction::Left:
        newCenter = { m_Center.x - SPEED, m_Center.y};
        break;
    }
    return newCenter;
};

Rect::Rect(Renderer& renderer, Coordinates center, float side)
    : Entity(renderer, center), m_Width(side), m_Height(side)
{
    float* positions = CalculatePosition();

    m_IndexBuffer.Update(indices, 6);
    
    m_VertexBuffer.Update(positions, 4 * 4 * sizeof(float));
    m_VertexBufferlayout.Push<float>(2);
    m_VertexBufferlayout.Push<float>(2);
    m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexBufferlayout);

    m_VertexArray.Unbind();
    m_VertexBuffer.Unbind();
    m_IndexBuffer.Unbind();
};

Rect::Rect(Renderer& renderer, Coordinates center, float width, float height)
    : Entity(renderer, center), m_Width(width), m_Height(height)
{
    float* positions = CalculatePosition();

    m_IndexBuffer.Update(indices, 6);

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

void Rect::Render(Shader &shader) const
{
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.0f, 0.3f, 1.0f, 1.0f);
    shader.SetUniformMat4f("u_MVP", proj);
    shader.Unbind();

    m_Renderer.Draw(m_VertexArray, m_IndexBuffer, shader);
};

void Rect::Move(Direction direction)
{
    m_Center = CalculateNewCenter(direction);
    float* positions = CalculatePosition();
    m_VertexBuffer.Update(positions, 4 * 4 * sizeof(float));
}
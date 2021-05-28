#pragma once

#include <iostream>
#include <string>

#include "Entity.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Particle : public Entity {
private:
    const float m_Speed = 1.0f;
    static const int m_Steps = 10;
    const float m_Beta = 3.1415926 * 2.0f / m_Steps;

    float m_Radius;

    std::vector<float> m_Positions;
    std::vector<unsigned int> m_Indices;

    VertexArray m_VertexArray;
    VertexBuffer m_VertexBuffer;
    VertexBufferLayout m_VertexBufferlayout;
    IndexBuffer m_IndexBuffer;

    float* CalculatePosition();
    Point CalculateNewCenter(Direction direction);
public:
    Particle()
        : m_Radius(0.0f) {};
    Particle(Point center, float radius);
    ~Particle();

    void Render(Renderer& renderer, Shader& shader) const;
    void Move(Direction direction);
};
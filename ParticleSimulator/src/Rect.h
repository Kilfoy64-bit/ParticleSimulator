#pragma once

#include <iostream>
#include <string>

#include "Entity.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class Rect : public Entity {
private:
    float m_Speed = 1.0f;
	float m_Width;
	float m_Height;
    Direction m_Direction = Direction::Stationary;

    std::vector<float> m_Positions;
    std::vector<unsigned int> m_Indices = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray m_VertexArray;
    VertexBuffer m_VertexBuffer;
    VertexBufferLayout m_VertexBufferlayout;
    IndexBuffer m_IndexBuffer;

    void updateBuffers();
    void calculatePosition();
    void moveDirection(Direction direction);

public: 
    Rect()
        : m_Speed(0.0f), m_Width(0.0f), m_Height(0.0f) {};
    Rect(Point2D center, float side);
    Rect(Point2D center, float width, float height);
	~Rect();

	void render(Renderer& renderer, Shader& shader) const;
    void update(long deltaTime);
};
#pragma once

#include <iostream>
#include <string>

#include "Entity.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"



class Rect : public Entity {
private:
    const float m_Speed = 1.0f;
	float m_Width;
	float m_Height;

    std::vector<float> m_Positions;
    std::vector<unsigned int> m_Indices = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray m_VertexArray;
    VertexBuffer m_VertexBuffer;
    VertexBufferLayout m_VertexBufferlayout;
    IndexBuffer m_IndexBuffer;

    void CalculatePosition();
    Point CalculateNewCenter(Direction direction);
public: 
    Rect()
        : m_Width(0.0f), m_Height(0.0f) {};
    Rect(Point center, float side);
    Rect(Point center, float width, float height);
	~Rect();

	void Render(Renderer& renderer, Shader& shader) const;
    void Move(Direction direction);
};
#pragma once

#include <iostream>
#include <string>

#include "Entity.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Rect : public Entity {
private:
    float SPEED = 1.0f;
	float m_Width;
	float m_Height;

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray m_VertexArray;
    VertexBuffer m_VertexBuffer;
    VertexBufferLayout m_VertexBufferlayout;
    IndexBuffer m_IndexBuffer;

    float* CalculatePosition();
    Coordinates CalculateNewCenter(Direction direction);
public: 
    Rect(Renderer& renderer)
        : Entity(renderer), m_Width(0.0f), m_Height(0.0f) {};
    Rect(Renderer& renderer, Coordinates center, float side);
    Rect(Renderer& renderer, Coordinates center, float width, float height);
	~Rect();

	void Render(Shader& shader) const;
    void Move(Direction direction);
};
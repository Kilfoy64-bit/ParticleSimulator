#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../Box/Box.h"
#include "../PhysicsEngine/Vector2D/Vector2D.h"
#include "../Entity/Entity.h"

#include "../GraphicsEngine/VertexArray/VertexArray.h"
#include "../GraphicsEngine/VertexBuffer/VertexBuffer.h"
#include "../GraphicsEngine/VertexBuffer/VertexBufferLayout.h"

#define PI 3.1415926f

class Particle : public Entity {
private:
    unsigned int m_Vertices = 30; // Represents number of triangular sections that approximate shape, use a high number to approximate a circle.
    float m_Radius;
    float m_Speed;
    Vector2D m_Velocity;

    float m_Beta = PI * 2.0f / m_Vertices;
    
    Box m_Container;

    void updateBuffers();

    void calculatePosition();
    void move(long deltaTime);
    void resolveContainerCollision();

public:
    Particle(Box &container)
        : m_Radius(0.0f), m_Speed(0.0f), m_Container(container) {};
    Particle(Point2D center, Box &container);
    ~Particle();

    bool detectParticleCollision(Particle other);
    
    inline Point2D getPosition() { return m_Position; }
    inline float getRadius() { return m_Radius; }

    inline void setVertices(unsigned int vertices) { m_Vertices = vertices; };
    inline void setSpeed(float speed) { m_Speed = speed; };
    inline void setRadius(float radius) { m_Radius = radius; };
    inline void setColor(std::vector<float> RGBA) { m_Color = RGBA; };

    void render(Renderer& renderer, Shader& shader) const;
    void update(long deltaTime);
};
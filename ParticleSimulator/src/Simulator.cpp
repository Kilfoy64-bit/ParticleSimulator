#include "Simulator.h"

#include "Rect.h"
#include "Particle.h"

void Simulator::generateRandomEntities()
{
    /*Entity* particleEntity = new Particle({ 500.0f, 500.0f }, m_Container);
    m_Entities.push_back(particleEntity);*/
    int particleToSimulate = 20;
    for (int i = 1; i <= particleToSimulate; i++) {
        //Entity* rectEntity = new Rect({ 0.0f + i, 700.0f }, 75);
        //m_Entities.push_back(rectEntity);

        Entity* particleEntity = new Particle({ i * 10.0f , 500.0f }, m_Container);
        m_Entities.push_back(particleEntity);
    }
}

void Simulator::clearScreen()
{
    m_Renderer.clear();
}

Simulator::Simulator(int width, int height, const char* name)
    : m_ScreenHeight(height), m_ScreenWidth(width), m_Name(name), m_Shader(Shader("res/shaders/Basic.shader")), m_Container(Box(width, height))
{
    generateRandomEntities();
}

Simulator::~Simulator()
{
    for (auto entity : m_Entities) {
        delete entity;
    }
}

void Simulator::playStep(long deltaTime)   
{
    clearScreen();

    for (unsigned int i = 0; i < m_Entities.size(); i++) {
        m_Entities[i]->update(deltaTime);
        m_Entities[i]->render(m_Renderer, m_Shader);
    }
}
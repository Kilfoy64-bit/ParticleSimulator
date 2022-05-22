#pragma once

#include "../GraphicsEngine/Renderer/Renderer.h"
#include "../GraphicsEngine/Shader/Shader.h"

#include "../Box/Box.h"
#include "../Entity/Entity.h"

class Simulator {
private:
	const char* m_Name;

	const float m_ScreenHeight;
	const float m_ScreenWidth;

	Box m_Container;

	Renderer m_Renderer;
	Shader m_Shader;
	std::vector<Entity*> m_Entities;

	void generateRandomEntities();
	void clearScreen();
public:
	Simulator(float width, float height, const char* name);
	~Simulator();

	void playStep(long deltaTime);

	inline float getHeight() const { return m_ScreenHeight; }
	inline float getWidth() const { return m_ScreenWidth; }
	inline const char* getName() const { return m_Name; }

	inline void setEntities(std::vector<Entity*> &entities) { m_Entities = entities; }
	inline void setRenderer(Renderer &renderer) { m_Renderer = renderer; }
	inline void setShader(Shader &shader) { m_Shader = shader; }
};
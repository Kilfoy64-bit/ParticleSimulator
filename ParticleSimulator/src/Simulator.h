#pragma once

#include "Renderer.h"
#include "Shader.h"

#include "Box.h"
#include "Entity.h"

class Simulator {
private:
	const char* m_Name;

	const int m_ScreenHeight = 1920;
	const int m_ScreenWidth = 1080;

	Box m_Container;

	Renderer m_Renderer;
	Shader m_Shader;
	std::vector<Entity*> m_Entities;

	void generateRandomEntities();
	void clearScreen();
public:
	Simulator(int width, int height, const char* name);
	~Simulator();

	void playStep(long deltaTime);

	inline int getHeight() const { return m_ScreenHeight; }
	inline int getWidth() const { return m_ScreenWidth; }
	inline const char* getName() const { return m_Name; }

	inline void setEntities(std::vector<Entity*> &entities) { m_Entities = entities; }
	inline void setRenderer(Renderer &renderer) { m_Renderer = renderer; }
	inline void setShader(Shader &shader) { m_Shader = shader; }
};
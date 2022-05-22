#pragma once

#include <GL/glew.h>

#include "../VertexArray/VertexArray.h"
#include "../IndexBuffer/IndexBuffer.h"
#include "../Shader/Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


class Renderer
{
public:
    void clear() const;
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
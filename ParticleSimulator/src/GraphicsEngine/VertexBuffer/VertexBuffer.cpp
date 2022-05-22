#include "../VertexBuffer/VertexBuffer.h"
#include "../Renderer/Renderer.h"

VertexBuffer::VertexBuffer()
{
    GLCall(glGenBuffers(1, &m_RendererID));
    update(nullptr, 0);
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    update(data, size);
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::update(const void* data, unsigned int size)
{
    bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

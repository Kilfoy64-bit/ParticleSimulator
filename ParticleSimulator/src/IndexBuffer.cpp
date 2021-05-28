#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer()
    : m_Count(0)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    Update(nullptr, m_Count);
}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    Update(data, m_Count);
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Update(const unsigned int* data, unsigned int count)
{
    m_Count = count;
    Bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

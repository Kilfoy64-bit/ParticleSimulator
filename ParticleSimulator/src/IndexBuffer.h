#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void update(const unsigned int* data, unsigned int count);
	void bind() const;
	void unbind() const;

	inline unsigned int getCount() const { return m_Count; }
};
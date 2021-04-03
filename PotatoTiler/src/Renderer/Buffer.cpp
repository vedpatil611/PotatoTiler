#include "Buffer.h"

#include <glad/glad.h>

Buffer::Buffer(const void* data, unsigned int count)
	:m_Count(count)
{
	glGenBuffers(1, &m_BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void Buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void Buffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

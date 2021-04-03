#include "VertexArray.h"

#include <glad/glad.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_BufferID);
}

VertexArray::~VertexArray()
{
	for (auto [index, buffer] : m_Buffers)
		delete buffer;

	glDeleteVertexArrays(1, &m_BufferID);
}

void VertexArray::addBuffer(unsigned int index, unsigned int cpb, Buffer* buffer)
{
	glBindVertexArray(m_BufferID);
	buffer->bind();

	m_Buffers.emplace(index, buffer);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, cpb, GL_FLOAT, false, 0, nullptr);
	
	buffer->unbind();
	glBindVertexArray(0);
}

void VertexArray::bind() const
{
	glBindVertexArray(m_BufferID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}


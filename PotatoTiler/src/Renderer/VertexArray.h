#pragma once

#include "Buffer.h"
#include <map>

class VertexArray
{
private:
	unsigned int m_BufferID;
	std::map<unsigned int, Buffer*> m_Buffers;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(unsigned int index, unsigned int cpb, Buffer* buffer);

	void bind() const;
	void unbind() const;
};
#pragma once

class IndexBuffer
{
private:
	unsigned int m_BufferID;
	unsigned int m_Count;
public:
	IndexBuffer(unsigned short* indicies, unsigned int count);
	~IndexBuffer();

	inline unsigned int getCount() const { return m_Count; }

	void bind() const;
	void unbind() const;
};
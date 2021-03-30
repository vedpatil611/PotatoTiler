#pragma once

class Buffer
{
private:
	unsigned int m_BufferID;
	unsigned int m_Count;
public:
	Buffer(const void* data, unsigned int count);
	~Buffer();

	inline unsigned int getCount() const { return m_Count; }

	void bind() const;
	void unbind() const;
};
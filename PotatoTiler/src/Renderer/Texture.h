#pragma once

class Texture
{
private:
	unsigned int m_TexID;
	
	int m_Height, m_Width, m_BPP;

public: 
	Texture(const char* path);
	~Texture();

	void bind(unsigned short slot = 0) const;
	void unbind() const;

	inline int getHeight() const { return m_Height; }
	inline int getWidth() const { return m_Width; }
};
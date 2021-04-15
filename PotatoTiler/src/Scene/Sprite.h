#pragma once

#include "Transform.h"

class Sprite
{
private:
	Transformation m_Transformation;
	class Shader* m_Shader = nullptr;
	class Texture* m_Texture = nullptr;
	class VertexArray* m_va;
	class IndexBuffer* m_ib;
public:
	Sprite(glm::vec2 pos, float rotation, glm::vec2 scale, Shader* shader, Texture* texture);
	~Sprite();
	
	void addVertexBuffer(unsigned int index, unsigned int cpb, class Buffer* buffer);
	void drawSprite();
};
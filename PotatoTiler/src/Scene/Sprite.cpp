#include "Sprite.h"

#include <glad/glad.h>
#include <Renderer/Shader.h>
#include <Renderer/VertexArray.h>
#include <Renderer/IndexBuffer.h>

Sprite::Sprite(glm::vec2 pos, float rotation, glm::vec2 scale, Shader* shader)
	: m_Transformation(pos, rotation, scale), m_Shader(shader)
{
	m_va = new VertexArray();

	unsigned short indicies[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	m_ib = new IndexBuffer(indicies, 2 * 3);
}

Sprite::~Sprite()
{
}

void Sprite::addVertexBuffer(unsigned int index, unsigned int cpb, Buffer* buffer)
{
	m_va->addBuffer(index, cpb, buffer);
}

void Sprite::drawSprite()
{
	m_va->bind();
	m_ib->bind();
	m_Shader->bind();

	glDrawElements(GL_TRIANGLES, m_ib->getCount(), GL_UNSIGNED_SHORT, nullptr);

	m_va->bind();
	m_ib->bind();
	m_Shader->bind();
}

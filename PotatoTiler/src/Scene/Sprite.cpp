#include "Sprite.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
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

	glm::vec2& t = m_Transformation.translation;
	glm::vec2& s = m_Transformation.scale;
	glm::mat4 model = glm::translate(glm::mat4(1.0f), { t.x, t.y, 0.0f });
	model = glm::rotate(model, m_Transformation.rotation, { 0.0f, 0.0f, 1.0f });
	model = glm::scale(model, { s.x, s.y, 1.0f });
	
	m_Shader->setUniformMat4("uModel", model);
	glDrawElements(GL_TRIANGLES, m_ib->getCount(), GL_UNSIGNED_SHORT, nullptr);

	m_va->bind();
	m_ib->bind();
	m_Shader->bind();
}

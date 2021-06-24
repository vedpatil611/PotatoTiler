#include "TextureArray.h"

TextureArray::TextureArray()
{

}

TextureArray::~TextureArray()
{
	for(auto* tex: m_Array)
		delete tex;
}

void TextureArray::pushTexture(Texture* tex)
{
	m_Array.push_back(tex);
}

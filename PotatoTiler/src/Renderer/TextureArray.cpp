#include "TextureArray.h"

#include <filesystem>
#include <string.h>

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

void TextureArray::pushTextureFromPath(const char *path)
{
	for(auto& entry: std::filesystem::directory_iterator(path))
	{
		if(!entry.is_directory())
		{
			auto path = entry.path();
			if(strcmp(path.extension().c_str(), ".png") == 0)
			{
				m_Array.push_back(new Texture(path.c_str()));
			}
		}
	}
}

void TextureArray::pushTextureFromPathRecursive(const char *path)
{
	for(auto& entry: std::filesystem::recursive_directory_iterator(path))
	{
		if(!entry.is_directory())
		{
			auto path = entry.path();
			if(strcmp(path.extension().c_str(), ".png") == 0)
			{
				m_Array.push_back(new Texture(path.c_str()));
			}
		}
	}
}

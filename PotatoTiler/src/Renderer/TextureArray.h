#include <vector>
#include <Renderer/Texture.h>

class TextureArray 
{
private:
	std::vector<Texture*> m_Array;
public:
	TextureArray();
	~TextureArray();

	void pushTexture(Texture* tex);
};


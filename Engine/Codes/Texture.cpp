#include "Texture.h"

using namespace Engine;

void Engine::Texture::AddIamge(ID2D1Bitmap* pImage)
{
	if (nullptr == pImage)
		return;

	_imageData.push_back(pImage);
}

void Engine::Texture::Free()
{
	for (auto& Image : _imageData)
		SafeRelease(Image);

	_imageData.clear();
	_imageData.shrink_to_fit();
}

Texture* Engine::Texture::Create()
{
	return new Texture;
}

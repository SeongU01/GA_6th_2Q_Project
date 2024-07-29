#pragma once

Engine::Texture* FindTexture(const wchar_t* textureTag)
{
	return Engine::ResourceManager::GetInstance()->FindTexture(textureTag);
}
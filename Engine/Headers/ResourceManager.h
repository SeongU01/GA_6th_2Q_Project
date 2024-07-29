#pragma once
#include "Base.h"
#include "Frame.h"

namespace Engine
{
	class Texture;
	class ResourceManager : public Base, public SingleTon<ResourceManager>
	{
		friend class SingleTon;
	private:
		using TextureData = std::unordered_map<std::wstring, Texture*>;
		using AnimationInfo = std::unordered_map<std::wstring, std::vector<Frame>>;
		using AnimationData = std::unordered_map<std::wstring, AnimationInfo>;
	private:
		explicit ResourceManager() = default;
		virtual ~ResourceManager() = default;
		NOCOPY(ResourceManager)

	public:
		void SetWICFactory(IWICImagingFactory* pWICFactory);
		bool LoadTexture(int slashOffset, const wchar_t* filePath);
		bool LoadAnimation(int slashOffset, const wchar_t* filePath);
		Texture* FindTexture(const wchar_t* textureTag);
		AnimationInfo FindAnimation(const wchar_t* animationTag);

	private:
		// Base을(를) 통해 상속됨
		void Free() override;
		bool CreateImage(ID2D1HwndRenderTarget* pRenderTarget, const wchar_t* filePath, ID2D1Bitmap** ppBitmap);
		bool CreateAnimation(const wchar_t* filePath, const wchar_t* animationTag);

	private:
		TextureData			_textureData;
		AnimationData		_animationData;
		IWICImagingFactory* _pWICFactory = nullptr;
	};
}


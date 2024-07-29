#pragma once
#include "Shader.h"

namespace Engine
{
	class ShaderVignette : public Shader
	{
	public:
		explicit ShaderVignette() = default;
		virtual ~ShaderVignette() = default;

	public:
		void SetValue(const D2D1_VECTOR_4F& color = {}, float transitionSize = 0.1f, float strength = 0.5f);

	public:
		// Shader을(를) 통해 상속됨
		void ComputeShader(ID2D1Bitmap* pBitmap) override;
		void Initialize(ID2D1DeviceContext* pDeviceContext) override;

	private:
		D2D1_VECTOR_4F _color{};
		float _transitionSize = 0.1f;
		float _strength = 0.5f;
	};
}
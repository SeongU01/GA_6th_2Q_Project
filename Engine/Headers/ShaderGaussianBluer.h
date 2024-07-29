#pragma once
#include "Shader.h"

namespace Engine
{
	class ShaderGaussianBluer : public Shader
	{
	public:
		explicit ShaderGaussianBluer() = default;
		virtual ~ShaderGaussianBluer() = default;

	public:
		void SetValue(float value) { _value = value; }

	public:
		// Shader을(를) 통해 상속됨
		void ComputeShader(ID2D1Bitmap* pBitmap) override;
		void Initialize(ID2D1DeviceContext* pDeviceContext) override;

	private:
		float _value = 3.f;
	};
}
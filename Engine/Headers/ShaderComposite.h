#pragma once
#include "Shader.h"

namespace Engine
{
	class ShaderComposite : public Shader
	{
	public:
		explicit ShaderComposite() = default;
		virtual ~ShaderComposite() = default;

	public:
		// Shader을(를) 통해 상속됨
		void CompositeShader(ID2D1Effect* pEffect1, ID2D1Effect* pEffect2);
		void ComputeShader(ID2D1Bitmap* pBitmap) override;
		void Initialize(ID2D1DeviceContext* pDeviceContext) override;

	private:

	};
}
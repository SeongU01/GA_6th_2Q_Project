#pragma once
#include "Base.h"

namespace Engine
{
	class Shader : public Base
	{
	protected:
		explicit Shader() = default;
		virtual ~Shader();

	public:
		ID2D1Effect* GetEffect() { return _pShaderEffect; }
		virtual void ComputeShader(ID2D1Bitmap* pBitmap) = 0;
		virtual void Initialize(ID2D1DeviceContext* pDeviceContext) = 0;

	private:
		void Free() override;

	protected:
		ID2D1Effect* _pShaderEffect = nullptr;
	};
}
#pragma once
#include "Shader.h"

namespace Engine
{
    class ShaderColor : public Shader
    {
    public:
        explicit ShaderColor() = default;
        virtual ~ShaderColor() = default;

    public:
        void SetColor(float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f);
        void SetUseColor(float r = 0.f, float g = 0.f, float b = 0.f, float a = 0.f);

    public:
        // Shader을(를) 통해 상속됨
        void ComputeShader(ID2D1Bitmap* pBitmap) override;
        void Initialize(ID2D1DeviceContext* pDeviceContext) override;

    private:
        D2D1_MATRIX_5X4_F _colorMatrix{};

    };
}
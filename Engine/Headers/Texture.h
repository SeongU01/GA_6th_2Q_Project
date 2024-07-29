#pragma once
#include "Base.h"

namespace Engine
{
    class Texture : public Base
    {
        friend class Animation;
        friend class ResourceManager;
    private:
        explicit Texture() = default;
        virtual ~Texture() = default;
 
    public:
        ID2D1Bitmap* GetImage(int index) const { return _imageData[index]; }
        ID2D1Bitmap* operator[](int index) const { return _imageData[index]; }
        void AddIamge(ID2D1Bitmap* pImage);

    private:
        void Free() override;

    public:
        static Texture* Create();

    private:
        std::vector<ID2D1Bitmap*> _imageData;
    };
}
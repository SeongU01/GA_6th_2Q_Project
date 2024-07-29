#pragma once
#include <d2d1.h>

struct Frame
{
    Frame(ID2D1Bitmap* pBitmap, float duration)
        : pBitmap(pBitmap), duration(duration) {}

    ID2D1Bitmap* pBitmap = nullptr;
    float duration = 0.f;
};
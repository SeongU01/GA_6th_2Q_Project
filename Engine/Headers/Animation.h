#pragma once
#include "Component.h"
#include "Texture.h"
#include "Frame.h"

namespace Engine
{    
    class Texture;
    class Animation : public Component
    {
        using AnimationData = std::unordered_map<std::wstring, std::vector<Frame>>;
    public:
        struct FrameEvent
        {
            std::function<void()> function;
            const wchar_t* animation = nullptr;
            int activeFrame = 0;
            bool isRepeat = false;
        };
    public:
        explicit Animation(const wchar_t* name);
    private:
        virtual ~Animation() = default;

    public:
        void Update(const float& deltaTime) override;
        void LateUpdate(const float& deltaTime) override;

    public:
        ID2D1Bitmap* GetCurrentImage();
        ID2D1Bitmap* GetImage(const int index);
        int GetCurrFrame() const { return _currIndex; }
        int GetLastFrame() { return (int)_animationData[_currAnimation].size() - 1; }
        void SetFrame(int frame);
        void SetLastFrame();
        void SetReversePlay(bool isActive);
        bool ChangeAnimation(const wchar_t* nextAnimation);
        bool IsCurrAnimation(const wchar_t* animation) const;
        bool IsLastFrame() const { return _isLastFrame; }
        bool IsBetweenFrame(const int first, const int last) const;
        bool LoadAnimation(const wchar_t* animationTag);
        void AddFrame(const wchar_t* animationTag, ID2D1Bitmap* pBitmap, const float& speed);
        void AddAllFrame(const wchar_t* animationTag, Texture* pTexture, const float& speed);
        void AddFrameEvent(const FrameEvent& event);

    private:
        // Component을(를) 통해 상속됨
        void Free() override;
        
    private:
        AnimationData           _animationData;
        std::list<FrameEvent>   _frameEvents;
        const wchar_t*          _currAnimation = 0;
        float                   _currFrame = 0.f;
        int                     _currIndex = 0;
        bool                    _isFrameChange = false;
        bool                    _isLastFrame = false;
        bool                    _isReverse = false;
    };
}
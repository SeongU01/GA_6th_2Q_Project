#include "Fade.h"
#include "Client_Define.h"

Fade::Fade(const FadeInfo& info)
    : MonoBehavior(L"Fade"), _fadeInfo(info)
{
}

void Fade::Awake()
{
    gameObject.SetRenderGroup((int)RenderGroup::Fade);
    _pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();

    switch (_fadeInfo.option)
    {
    case Fade::Fade_In:
        _fadeInfo.alpha = 1.f;
        break;
    case Fade::Fade_OutIn:
    case Fade::Fade_Out:
        _fadeInfo.alpha = 0.f;
        break;
    }

    _drawRect.left = 0.f;
    _drawRect.top = 0.f;
    _drawRect.right = (float)WINCX;
    _drawRect.bottom = (float)WINCY;

    _pSpriteRenderer->SetOneSelfDraw(true, [this]() { _pSpriteRenderer->DrawFillRect(_drawRect, _fadeInfo.color, _fadeInfo.alpha); });
}

void Fade::Start()
{
}

void Fade::Update(const float& deltaTime)
{
    float _deltaTime = Time::GetGlobalDeltaTime();
    _elapsed +=_deltaTime;

    switch (_fadeInfo.option)
    {
    case Fade::Fade_In:
        _fadeInfo.alpha -= _deltaTime / _fadeInfo.duration;
        if (0.f >= _fadeInfo.alpha) _fadeInfo.alpha = 0.f;
        break;

    case Fade::Fade_Out:
        _fadeInfo.alpha += _deltaTime / _fadeInfo.duration;
        if (1.f <= _fadeInfo.alpha) _fadeInfo.alpha = 1.f;
        break;

    case Fade::Fade_OutIn:
        if (_elapsed >= _fadeInfo.delay)
        {
            if (!_isOutIn)
            {
                _fadeInfo.alpha += _deltaTime / _fadeInfo.duration;
                if (1.f <= _fadeInfo.alpha)
                {
                    _fadeInfo.alpha = 1.f;
                    _elapsed = _fadeInfo.delay;
                    _isOutIn = true;
                }
            }
            else
            {
                if (_fadeInfo.outInDelay <= _elapsed - _fadeInfo.delay)
                {
                    _fadeInfo.alpha -= _deltaTime / _fadeInfo.duration;
                    if (0.f >= _fadeInfo.alpha)
                    {
                        _fadeInfo.alpha = 0.f;
                        gameObject.SetDead();
                    }
                }
            }
        }
        break;
    }
}

void Fade::LateUpdate(const float& deltaTime)
{
    if (_elapsed >= _fadeInfo.life)
        gameObject.SetDead();
}
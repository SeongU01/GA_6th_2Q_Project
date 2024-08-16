#include "Effect.h"
#include "Animation.h"

#include "Client_Define.h"

Effect::Effect(const EffectInfo& info)
    : MonoBehavior(L"Effect"), _info(info)
{
}

void Effect::Awake()
{
    gameObject.SetRenderGroup((int)_info.renderGroup);

    // Transform
    transform.SetParent(_info.pTarget);
    transform.position = _info.position;
    transform.direction =_info.direction;
    transform.scale = _info.scale;
    transform.rotation = Vector3(0.f, 0.f, _info.rotation);

    // Component
    _pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();

    if (nullptr != _info.textureTag)
    {
        _pAnimation = AddComponent<Engine::Animation>(L"Animation");
        _pSpriteRenderer->BindAnimation(_pAnimation);
        _pAnimation->AddAllFrame(L"Effect", Resource::FindTexture(_info.textureTag), _info.aniSpeed);

        if (_info.isFixFrame)
            _pAnimation->SetFrame(_info.fixFrame);

        _pAnimation->ChangeAnimation(L"Effect");
    }

    _originSpeed = _info.speed;
    _pSpriteRenderer->SetDrawOffset(_info.drawOffset);

    _color = { 1.f, 1.f, 1.f, 1.f };

    _pSpriteRenderer->SetOneSelfDraw(true, [this]()
        {
            if (nullptr != _info.textureTag)
                _pSpriteRenderer->Draw();
            else
                _pSpriteRenderer->Draw(_info.pBitmap);
        });    
}

void Effect::Start()
{
}

void Effect::Update(const float& deltaTime)
{
    float offset = 0.f;
    _elapsed += deltaTime;

    if (_info.isFadeOut)
    {
        if (_info.isActiveLife)
        {
            offset = _info.fadeSpeed;
            if (_info.life <= _elapsed + offset)
            {
                _alpha -= deltaTime / offset;
                if (0.f > _alpha) _alpha = 0.f;
                _pSpriteRenderer->GetShader<Engine::ShaderColor>()->SetColor(_color.x, _color.y, _color.z, _alpha);
            }
        }
        else
        {
            if (_isLastFrame)
            {
                _alpha -= deltaTime / _info.fadeSpeed;
                if (0.f > _alpha) _alpha = 0.f;
                _pSpriteRenderer->GetShader<Engine::ShaderColor>()->SetColor(_color.x, _color.y, _color.z, _alpha);
            }
        }
    }

    if (_info.pTarget)
    {
        transform.position = _info.position;
    }
    else
    {
        if (_info.life >= _elapsed - offset)
        {
            if (_info.isDecelerate)
                _info.speed -= _originSpeed * deltaTime / _info.life;

            if (_info.isFalling)
            {
                transform.position += Vector3(0.f, 1.f, 0.f) * deltaTime * (_originSpeed - _info.speed);
            }

            transform.position += Vector3(transform.direction * _info.speed * deltaTime);
        }
    }
}

void Effect::LateUpdate(const float& deltaTime)
{
    if (!_info.isInfinity)
    {

        if (_info.isActiveLife)
        {
            if (_info.life + _info.fadeSpeed <= _elapsed)
                gameObject.SetDead();
        }
        else if (_info.isFadeOut)
        {
            if (_pAnimation->IsLastFrame())
            {
                _isLastFrame = true;
                _pAnimation->SetLastFrame();
            }
        }
        else
        {
            if (_pAnimation->IsLastFrame())
                gameObject.SetDead();
        }                
    }

    if (_info.isFixFrame)
        _pAnimation->SetFrame(_info.fixFrame);

    if (_info.isOnePlay && _pAnimation->IsLastFrame())
        _pAnimation->SetLastFrame();
}

void Effect::SetUseColor(float r, float g, float b, float a)
{
    _pSpriteRenderer->GetShader<Engine::ShaderColor>()->SetUseColor(r, g, b, a);
}

void Effect::SetColor(const XMFLOAT4& color)
{
    _color = color;
    _alpha = color.w;
    _pSpriteRenderer->GetShader<Engine::ShaderColor>()->SetColor(color.x, color.y, color.z, color.w);
}

void Effect::SetFadeOut(bool isActive, float speed)
{
    _info.isFadeOut = isActive;
    _info.fadeSpeed = speed;
}

void Effect::SetAlpha(float alpha)
{
    _alpha = alpha;
    _pSpriteRenderer->GetShader<Engine::ShaderColor>()->SetColor(1.f, 1.f, 1.f, _alpha); 
}

void Effect::SetFixFrame(int frame)
{
    _info.fixFrame = frame;
}

void Effect::SetRotation(float degree)
{
    transform.rotation = Vector3(0.f, 0.f, degree);
}

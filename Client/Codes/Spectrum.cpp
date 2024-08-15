#include "Spectrum.h"

// Component
#include "Effect.h"
#include "Animation.h"

#include "Client_Define.h"

Spectrum::Spectrum(float interval, const Vector3& drawOffset, const Vector3& size)
	: MonoBehavior(L"Spectrum"), _interval(interval), _drawOffset(drawOffset), _size(size)
{
}

void Spectrum::Awake()
{
	_pAnimation = GetComponent<Engine::Animation>();
	_elapsed = _interval;
	_useColor = { 0.515f, 0.976f, 0.781f, 0.f };
	_color = { 1.f, 1.f, 1.f, 0.5f };
	SetActive(false);
}

void Spectrum::Start()
{
}

void Spectrum::Update(const float& deltaTime)
{
	if (!IsActive())
		return;

	_elapsed += deltaTime;

	if (_elapsed > _interval)
	{
		_elapsed = 0.f;

		auto pEffect = Engine::GameObject::Create();

		Effect::EffectInfo info;
		info.pBitmap = _pAnimation->GetCurrentImage();
		info.renderGroup = RenderGroup::BackEffect;
		info.position = transform.position;
		info.isActiveLife = true;
		info.life = 0.3f;
		info.isFadeOut = true;
		info.fadeSpeed = 0.6f;
		info.drawOffset = _drawOffset;
		
		Effect* effectComponent = pEffect->AddComponent<Effect>(info);
		effectComponent->SetUseColor(_useColor.x, _useColor.y, _useColor.z);
		effectComponent->SetColor(_color);
		Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);
	}
}

void Spectrum::LateUpdate(const float& deltaTime)
{
}

void Spectrum::Reset()
{
	_useColor = { 0.515f, 0.976f, 0.781f, 0.f };
	_color = { 1.f, 1.f, 1.f, 1.f };
	SetActive(false);
}

void Spectrum::SetColor(const XMFLOAT4& useColor, const XMFLOAT4& color)
{
	_useColor = useColor;
	_color = color;
}

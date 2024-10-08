#include "PlayerMP.h"
#include "GageHUD.h"
#include "Client_Define.h"

constexpr float RECOVERYCOOLTIME = 3.f;

PlayerMP::PlayerMP(const wchar_t* name)
	:MonoBehavior(name)
{
}

void PlayerMP::Awake()
{
	Engine::GameObject* _pObj = Engine::GameObject::Create();
	_pGageHUD = _pObj->AddComponent<GageHUD>(Vector3(160.f, 920.f, 0.f), &_mpRecoveryTime, RECOVERYCOOLTIME, 0);
	_pGageHUD->SetDontDestroyObjectUI(true);
	_pObj->SetDontDestroyObject(true);
	_pObj->SetRenderGroup((int)RenderGroup::None);
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", _pObj);
}

void PlayerMP::Start()
{
}

void PlayerMP::Update(const float& deltaTime)
{
	MPUpdate(deltaTime);
}

void PlayerMP::LateUpdate(const float& deltaTime)
{
}

void PlayerMP::SetPlayerActivies(bool _isActive)
{
	_pGageHUD->SetActives(_isActive);
}

void PlayerMP::MPUpdate(const float& deltaTime)
{
	if (_mp < 5) NaturalRecovery(deltaTime);
	_mp = std::clamp(_mp, 0, 5);
}

void PlayerMP::NaturalRecovery(const float& deltaTime)
{
	_mpRecoveryTime += deltaTime;

	if (_mpRecoveryTime >= RECOVERYCOOLTIME)
	{
		Sound::PlaySound("Card_Sound_Mana_Recharge", (int)SoundGroup::AddSFX, 0.8f, false);
		_mp++;
		_mpRecoveryTime = 0.f;
	}
}

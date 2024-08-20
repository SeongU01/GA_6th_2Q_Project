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
	auto pGameObject = Engine::GameObject::Create();
	GageHUD* pGageHUD = pGameObject->AddComponent<GageHUD>(Vector3(160.f, 920.f, 0.f), &_mpRecoveryTime, RECOVERYCOOLTIME, 0);
	pGageHUD->SetDontDestroyObjectUI(true);
	pGameObject->SetDontDestroyObject(true);
	pGameObject->SetRenderGroup((int)RenderGroup::None);
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pGameObject);
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

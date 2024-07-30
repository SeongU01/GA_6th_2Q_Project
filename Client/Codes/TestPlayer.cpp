#include "TestPlayer.h"
#include "BitFlag.h"
#include "PlayerComponent.h"
#include "Client_Define.h"

enum Flag : unsigned long long { Attack, Move, Idle };

void TestPlayer::Initialize()
{
	Engine::BitFlag* pBitFlag = nullptr;

	pBitFlag->OnFlag(Flag::Attack | Idle);
	pBitFlag->CheckFlag(Flag::Move | Idle);

	AddComponent<PlayerComponent>("PC");
	_pSpriteRenderer->BindTexture(Resource::FindTexture(L"Test"));
	_pTransform->position = Vector3(WINCX >> 1, WINCY >> 1, 0.f);
	SetRenderGroup((int)RenderGroup::Object);
}

TestPlayer* TestPlayer::Create()
{
	TestPlayer* pInstance = new TestPlayer;
	pInstance->Initialize();

	return pInstance;
}

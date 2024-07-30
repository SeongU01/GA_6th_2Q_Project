#include "TestPlayer.h"
#include "Player.h"
#include "Client_Define.h"

enum Flag : unsigned long long { Attack, Move, Idle };

void TestPlayer::Initialize()
{
	AddComponent<Player>("PC");

	_pTransform->position = Vector3(WINCX >> 1, WINCY >> 1, 0.f);
	_pSpriteRenderer->BindTexture(Resource::FindTexture(L"Test"));

	SetRenderGroup((int)RenderGroup::Object);
}

TestPlayer* TestPlayer::Create()
{
	TestPlayer* pInstance = new TestPlayer;
	pInstance->Initialize();

	return pInstance;
}

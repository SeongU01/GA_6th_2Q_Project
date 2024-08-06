#include "TestPlayer.h"
#include "Player.h"
#include "Client_Define.h"

enum Flag : unsigned long long { Attack, Move, Idle };

void TestPlayer::Initialize()
{
	AddComponent<Player>(L"PlayerComponent");
	_pSpriteRenderer->BindTexture(Resource::FindTexture(L"Player"));

	SetRenderGroup((int)RenderGroup::Player);
}

TestPlayer* TestPlayer::Create()
{
	TestPlayer* pInstance = new TestPlayer;
	pInstance->Initialize();

	return pInstance;
}

#include "TestPlayer.h"
#include "Player.h"
#include "Client_Define.h"
#include "GridMovement.h"
#include "Grid.h"

enum Flag : unsigned long long { Attack, Move, Idle };

void TestPlayer::Initialize()
{
	SetDontDestroyObject(true);
	AddComponent<Player>(L"PlayerComponent");
	_pSpriteRenderer->BindTexture(Resource::FindTexture(L"Player"));

	SetRenderGroup((int)RenderGroup::Object);
}

void TestPlayer::ChangeCurrentGrid()
{
	GridMovement* pMovement = GetComponent<GridMovement>();
	pMovement->Start();
	Player* pPlayerSpcript = GetComponent<Player>();
	pPlayerSpcript->Start();
}

TestPlayer* TestPlayer::Create()
{
	TestPlayer* pInstance = new TestPlayer;
	pInstance->Initialize();

	return pInstance;
}

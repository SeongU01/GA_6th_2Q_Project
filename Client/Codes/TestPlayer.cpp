#include "TestPlayer.h"
//script
#include "PlayerMP.h"
#include "Player.h"
#include "Client_Define.h"
#include "GridMovement.h"
#include "Grid.h"

enum Flag : unsigned long long { Attack, Move, Idle };

void TestPlayer::Initialize(const Vector3& startPos)
{
	SetDontDestroyObject(true);
	AddComponent<Player>(L"PlayerComponent",startPos);
	AddComponent<PlayerMP>(L"MP");
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

TestPlayer* TestPlayer::Create(const Vector3& startPos)
{
	TestPlayer* pInstance = new TestPlayer;
	pInstance->Initialize(startPos);

	return pInstance;
}

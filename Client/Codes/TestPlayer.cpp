#include "TestPlayer.h"

//Script
#include "Player.h"
#include "GridMovement.h"
#include "Grid.h"
#include "Client_Define.h"

enum Flag : unsigned long long { Attack, Move, Idle };

void TestPlayer::Initialize(const Vector3& startPos)
{
	SetDontDestroyObject(true);
	AddComponent<Player>(L"PlayerComponent",startPos);	

	_pSpriteRenderer->BindTexture(Resource::FindTexture(L"Player"));
	_pSpriteRenderer->SetDrawOffset(Vector3(20.f, -100.f, 0.f));
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

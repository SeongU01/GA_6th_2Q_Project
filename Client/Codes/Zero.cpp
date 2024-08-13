#include "Zero.h"

//Script
#include "Player.h"
#include "GridMovement.h"
#include "Grid.h"
#include "Client_Define.h"

enum Flag : unsigned long long { Attack, Move, Idle };

void Zero::Initialize(const Vector3& startPos)
{
	SetDontDestroyObject(true);
	AddComponent<Player>(L"PlayerComponent",startPos);	

	_pSpriteRenderer->BindTexture(Resource::FindTexture(L"Player"));
	SetRenderGroup((int)RenderGroup::Object);
}

void Zero::ChangeCurrentGrid()
{
	GridMovement* pMovement = GetComponent<GridMovement>();
	pMovement->Start();
	Player* pPlayerSpcript = GetComponent<Player>();
	pPlayerSpcript->Start();
}

Zero* Zero::Create(const Vector3& startPos)
{
	Zero* pInstance = new Zero;
	pInstance->Initialize(startPos);

	return pInstance;
}

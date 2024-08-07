#include "Enemy.h"
#include "TestEnemy.h"
#include "Client_Define.h"

enum Flag : unsigned long long { Attack, Move, Idle };

void TestEnemy::Initialize()
{
	AddComponent<Enemy>(L"EnemyComponent");
	_pSpriteRenderer->BindTexture(Resource::FindTexture(L"Player"));

	SetRenderGroup((int)RenderGroup::Object);
}

TestEnemy* TestEnemy::Create()
{
	TestEnemy* pInstance = new TestEnemy;
	pInstance->Initialize();

	return pInstance;
}

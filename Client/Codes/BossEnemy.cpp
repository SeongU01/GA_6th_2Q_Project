#include "BossEnemy.h"
//script
#include "BossEnemyScript.h"

#include "Client_Define.h"

void BossEnemy::Initialize(const Vector3& startPos, const std::wstring& _targetName)
{
	_pSpriteRenderer->SetDrawOffset(Vector3(20.f, -100.f, 0.f));
	AddComponent<BossEnemyScript>(L"Script", startPos, _targetName);
	SetRenderGroup((int)RenderGroup::Object);
}

BossEnemy* BossEnemy::Create(const Vector3& startPos, const std::wstring& _targetName)
{
	BossEnemy* pInstance = new BossEnemy;
	pInstance->Initialize(startPos, _targetName);

	return pInstance;
}

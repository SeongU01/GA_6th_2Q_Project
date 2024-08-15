#include "EliteEnemy.h"
//script
#include "EliteEnemyScript.h"

#include "Client_Define.h"

void EliteEnemy::Initialize(const Vector3& startPos, const std::wstring& _targetName)
{
	_pSpriteRenderer->SetDrawOffset(Vector3(20.f, -100.f, 0.f));
	AddComponent<EliteEnemyScript>(L"Script", startPos, _targetName);
	SetRenderGroup((int)RenderGroup::Object);

}

EliteEnemy* EliteEnemy::Create(const Vector3& startPos, const std::wstring& _targetName)
{
	EliteEnemy* pInstance = new EliteEnemy;
	pInstance->Initialize(startPos, _targetName);

	return pInstance;
}

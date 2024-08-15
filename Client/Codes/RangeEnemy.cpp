#include "RangeEnemy.h"

//script
#include "RangeEnemyScript.h"

#include "Client_Define.h"

void RangeEnemy::Initialize(const Vector3& startPos, const std::wstring& _targetName)
{
	_pSpriteRenderer->BindTexture(Resource::FindTexture(L"Enemy_Default_Idle"));
	_pSpriteRenderer->SetDrawOffset(Vector3(20.f, -100.f, 0.f));
	AddComponent<RangeEnemyScript>(L"Script", startPos, _targetName);
	SetRenderGroup((int)RenderGroup::Object);

}

RangeEnemy* RangeEnemy::Create(const Vector3& startPos, const std::wstring& _targetName)
{
	RangeEnemy* pInstance = new RangeEnemy;
	pInstance->Initialize(startPos, _targetName);

	return pInstance;
}

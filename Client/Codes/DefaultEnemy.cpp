#include "DefaultEnemy.h"

//script
#include "DefaultEnemyScript.h"

#include "Client_Define.h"

void DefaultEnemy::Initialize(const Vector3& startPos, const std::wstring& _targetName)
{
	_pSpriteRenderer->SetDrawOffset(Vector3(20.f, -100.f, 0.f));
	AddComponent<DefaultEnemyScript>(L"Script",startPos,_targetName);
	SetRenderGroup((int)RenderGroup::Object);
	
}

DefaultEnemy* DefaultEnemy::Create(const Vector3& startPos, const std::wstring& _targetName)
{
	DefaultEnemy* pInstance = new DefaultEnemy;
	pInstance->Initialize(startPos,_targetName);

	return pInstance;
}
 
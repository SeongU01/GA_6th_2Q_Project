#include "DefaultEnemy.h"

//script
#include "DefaultEnemyScript.h"
#include "HP.h"

#include "Client_Define.h"

void DefaultEnemy::Initialize(const Vector3& startPos)
{
	_pSpriteRenderer->BindTexture(Resource::FindTexture(L"Enemy_Default_Idle"));
	_pSpriteRenderer->SetDrawOffset(Vector3(20.f, -100.f, 0.f));
	AddComponent<DefaultEnemyScript>(L"Script",startPos);
	AddComponent<HP>(L"HP", 5);
	SetRenderGroup((int)RenderGroup::Object);
	
}

DefaultEnemy* DefaultEnemy::Create(const Vector3& startPos)
{
	DefaultEnemy* pInstance = new DefaultEnemy;
	pInstance->Initialize(startPos);

	return pInstance;
}

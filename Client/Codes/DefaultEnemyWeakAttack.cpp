#include "DefaultEnemyWeakAttack.h"
#include "Animation.h"
int DefaultEnemyWeakAttack::Update(const float& deltaTime)
{
  
    return 0;
}

int DefaultEnemyWeakAttack::LateUpdate(const float& deltaTime)
{
  if (_pAnimation->IsLastFrame())
  {
    return (int)DefaultEnemy::FSM::Idle;
  }
    return 0;
}

void DefaultEnemyWeakAttack::OnStart()
{
  _pAnimation->ChangeAnimation(L"Attack");
}

void DefaultEnemyWeakAttack::OnExit()
{
  _pAnimation->ChangeAnimation(L"Idle");
}

DefaultEnemyWeakAttack* DefaultEnemyWeakAttack::Create(DefaultEnemyScript* pScript)
{
  DefaultEnemyWeakAttack* pInstance = new DefaultEnemyWeakAttack;
  pInstance->DefaultEnemyState::Initialize(pScript);
  return pInstance;
}

#include "DefaultEnemyWeakAttack.h"
//component
#include "Animation.h"
#include "Pannel.h"
#include "TextRenderer.h"
#include "GridEffect.h"
#include "AttackCollider.h"
#include "Effect.h"
#include "GridMovement.h"
#include "Grid.h"

#include "DefaultEnemyScript.h"
#include "DataManager.h"
#include "Client_Define.h"
int DefaultEnemyWeakAttack::Update(const float& deltaTime)
{
  if (!_isStateOn)
  {
    if (_pAnimation->IsCurrAnimation(L"Idle"))
      _currTime += deltaTime;

    if (_currTime >= _delayTime)
    {
      _currTime = _delayTime;
      _pAnimation->ChangeAnimation(L"WeakAttack");
      //TODO : 진짜 때리기
      _isStateOn = true;
    }
  }
  return 0;
}

int DefaultEnemyWeakAttack::LateUpdate(const float& deltaTime)
{
  if(!_isStateOn)
    ShowInfo();
  
  if (_isStateOn &&  _pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"WeakAttack"))
    return (int)DefaultEnemy::FSM::Idle;
  return 0;
}

void DefaultEnemyWeakAttack::OnStart()
{
  _isStateOn = false;
  _currTime = 0.f;
  _delayTime = (float)Engine::RandomGeneratorInt(2,4);
}

void DefaultEnemyWeakAttack::OnExit()
{
  CloseInfo();
}

void DefaultEnemyWeakAttack::ShowInfo()
{
    __super::ShowInfo();
  if (_pAnimation->IsCurrAnimation(L"Idle"))
  {
    ShowAttackRange();
  }
  _pTextRenderer->SetOffset(Vector3(-60.f, -15.f, 0.f));
  std::wstringstream wss;
  wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
  std::wstring timeString = wss.str();

  _infoText = L"[Attack] " + timeString + L" s";
  _pTextRenderer->SetText(_infoText.c_str());
}

void DefaultEnemyWeakAttack::CloseInfo()
{
    __super::CloseInfo();
}

void DefaultEnemyWeakAttack::Attack()
{
  auto pEffect = Engine::GameObject::Create();
  Effect::EffectInfo info;
  info.renderGroup = RenderGroup::FrontEffect;
  info.aniSpeed = 0.03f;
  info.textureTag = L"AIEffect_Attack_Anim_VFX_Round_E";
  info.position = _pOwner->transform.position;
  info.scale = _pOwner->transform.scale * 0.7f;
  pEffect->AddComponent<Effect>(info);
  Engine::AddObjectInLayer((int)LayerGroup::Object, L"Effect", pEffect);


  AttackCollider* pAttackCollider = _pOwner->GetComponent<AttackCollider>();
  AttackCollider::AttackInfo attackInfo;
  attackInfo.damage = 1;
  const Vector3& gridPosition = *_pGridPosition;
  std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(11);
  for (auto& range : ranges)
  {
    int x = int(range.first + gridPosition.x);
    int y = int(range.second + gridPosition.y);
    pAttackCollider->OnCollider(0.01f, 0.05f, x, y, attackInfo, 0);
  }
}

void DefaultEnemyWeakAttack::ShowAttackRange()
{
  const Vector3& gridPosition = *_pGridPosition;
  std::vector<std::pair<int, int>> ranges =DataManager::GetInstance()->GetAttackRange(11);
  int index = 1;
  for (auto& grid : ranges)
  {
    _pGridEffect->OnEffect(int(gridPosition.x+grid.first), int(gridPosition.y+ grid.second), index);
  }
}

DefaultEnemyWeakAttack* DefaultEnemyWeakAttack::Create(DefaultEnemyScript* pScript)
{
  DefaultEnemyWeakAttack* pInstance = new DefaultEnemyWeakAttack;
  pInstance->DefaultEnemyState::Initialize(pScript);
  Engine::Animation::FrameEvent frameEvent;
  frameEvent.activeFrame = 6;
  frameEvent.animation = L"WeakAttack";
  frameEvent.isRepeat = true;
  frameEvent.function = [pInstance]()
    {
      pInstance->Attack();
    };
  pInstance->_pAnimation->AddFrameEvent(frameEvent);
  return pInstance;
}

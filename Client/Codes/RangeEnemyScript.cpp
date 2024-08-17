#include "RangeEnemyScript.h"
#include "Grid.h"
#include "GameObject.h"
//component
#include "FiniteStateMachine.h"
#include "Animation.h"
#include "GridMovement.h"
#include "Astar.h"
#include "HP.h"
#include "HPHUD.h"
#include "Collider.h"
#include "Pannel.h"
#include "Player.h"
#include "TextRenderer.h"
//state
#include "RangeEnemyIdle.h"
#include "RangeEnemyForwardMove.h"
#include "RangeEnemyBackMove.h"
#include "RangeEnemyAttack.h"
#include "RangeEnemySupport.h"

#include "RangeEnemyInformation.h"
#include "Client_Define.h"

RangeEnemyScript::RangeEnemyScript(const wchar_t* name, const Vector3& startPos, const std::wstring& _targetName)
	:MonoBehavior(name), _startPosition(startPos), _targetObjectName(_targetName)
{

}

void RangeEnemyScript::Awake()
{
	Engine::Collider* pCollider = AddComponent<Engine::Collider>(L"Body");
	pCollider->SetScale(Vector3(90.f, 90.f, 0.f));

#ifdef _DEBUG
	_pOwner->_isDrawCollider = true;
#endif // _DEBUG

	//TODO: FSM �ۼ��ϱ�
	_pHP = AddComponent<HP>(L"HP", 5);
	AddComponent<HPHUD>(_pHP, 1);
	_aStar = AddComponent<AStar>(L"AStar", _targetObjectName);
	_movement = AddComponent<GridMovement>(L"Movement", 500.f);
	_pAnimation = AddComponent<Engine::Animation>(L"Animation");
	if (false == _pAnimation->LoadAnimation(L"Enemy_Range_RangeEnemy"))
		throw std::runtime_error("can't load animation!");
	_pAnimation->ChangeAnimation(L"Idle");
	Engine::SpriteRenderer* pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();
	pSpriteRenderer->BindAnimation(_pAnimation);

	Pannel::PannelInfo info;
	info.parent = &transform;
	info.position = Vector3(0.f, -170.f, 0.f);
	info.size = Vector3{ 200, 50, 0 }; //ũ��
	info.fillColor = 0x99AEAEAE; //����
	info.outlineColor = 0xFF000000; //�׵θ� ����
	info.opacity = 0.4f;
	_pPannel = Pannel::Create(info);
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Ememyinfo", _pPannel);
	_pPannel->AddComponent<Engine::TextRenderer>(L"TextRenderer", D2D1::ColorF::Black, 20.f);
	_pPannel->SetActive(false);

	_pToolTip = AddComponent<ToolTip>(L"RangeToolTip");
	_pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Character_002"), Vector3(0.0f, 0.0f, 0.0f));

}

void RangeEnemyScript::Start()
{
	_pTargetObject = Engine::FindObject((int)LayerGroup::Player, L"Player",NULL);
	_pDefense = _pTargetObject->GetComponent<Player>();
	_gridPosition = _startPosition;
	_targetPosition = _pDefense->GetGridPosition();
	_aStar->SetGridMovement(_movement);
	_aStar->SetGoalPosition(_pDefense->GetGridPosition());
	_aStar->SetGridPosition(_startPosition);
	transform.position = _movement->_grid->GetTileCenter((int)_gridPosition.x, (int)_gridPosition.y);


	_pFSM = AddComponent<Engine::FiniteStateMachine>(L"FSM", (int)RangeEnemy::FSM::End);
	_pFSM->AddState((int)RangeEnemy::FSM::Idle, RangeEnemyIdle::Create(this));
	_pFSM->AddState((int)RangeEnemy::FSM::Attack, RangeEnemyAttack::Create(this));
	_pFSM->AddState((int)RangeEnemy::FSM::ForwardMove, RangeEnemyForwardMove::Create(this));
	_pFSM->AddState((int)RangeEnemy::FSM::BackMove, RangeEnemyBackMove::Create(this));
	_pFSM->AddState((int)RangeEnemy::FSM::Support, RangeEnemySupport::Create(this));
	_pFSM->ChangeState((int)RangeEnemy::FSM::Idle);
}

void RangeEnemyScript::Update(const float& deltaTime)
{
	_targetPosition = _pDefense->GetGridPosition();
	if (Input::IsKeyDown(DIK_M))
	{
		gameObject.SetDead();
	}
}

void RangeEnemyScript::LateUpdate(const float& deltaTime)
{
}

void RangeEnemyScript::OnCollisionEnter(Engine::CollisionInfo& info)
{

}

void RangeEnemyScript::OnCollision(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();
	if (*pOther == L"Mouse")
	{
		RangeEnemyState* currState = dynamic_cast<RangeEnemyState*>(_pFSM->GetCurrState(_pFSM->GetCurrState()));
		currState->ShowInfo();
	}
}

void RangeEnemyScript::OnCollisionExit(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();
	if (*pOther == L"Mouse")
	{
		RangeEnemyState* currState = dynamic_cast<RangeEnemyState*>(_pFSM->GetCurrState(_pFSM->GetCurrState()));
		currState->CloseInfo();
	}
}


#include "DefaultEnemyScript.h"
#include "Grid.h"
//component
#include "FiniteStateMachine.h"
#include "Animation.h"
#include "GridMovement.h"
#include "Astar.h"
#include "HP.h"

#include "Defense.h"
#include "DefenseScript.h"
//state
#include "DefaultEnemyIdle.h"
#include "DefaultEnemyMove.h"

#include "DefaultEnemyInfomation.h"
#include "Client_Define.h"

DefaultEnemyScript::DefaultEnemyScript(const wchar_t* name, const Vector3& startPos, const std::wstring& _targetName)
	:MonoBehavior(name),_startPosition(startPos),_targetObjectName(_targetName)
{
	
}

void DefaultEnemyScript::Awake()
{
	//TODO: FSM 작성하기
	_pHP=AddComponent<HP>(L"HP", 5);
	_aStar = AddComponent<AStar>(L"AStar",_targetObjectName);
	_movement = AddComponent<GridMovement>(L"Movement",500.f);
	_pAnimation = AddComponent<Engine::Animation>(L"Animation");
	if (false == _pAnimation->LoadAnimation(L"Enemy_Default_DefaultEnemy"))
		throw std::runtime_error("can't load animation!");
	_pAnimation->ChangeAnimation(L"Idle");
	Engine::SpriteRenderer* pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();
	pSpriteRenderer->BindAnimation(_pAnimation);

	
}

void DefaultEnemyScript::Start()
{
	_pTargetObject = Engine::FindObject((int)LayerGroup::Object, L"Defense", _targetObjectName.c_str());
	_pDefense = _pTargetObject->GetComponent<DefenseScript>(L"DefenseScript");
	_gridPosition = _startPosition;
	_targetPosition = _pDefense->GetGridPosition();
	_aStar->SetGridMovement(_movement);
	_aStar->SetGoalPosition(_pDefense->GetGridPosition());
	_aStar->SetGridPosition(_startPosition);
	transform.position = _movement->_grid->GetTileCenter((int)_gridPosition.x, (int)_gridPosition.y);

	_pFSM = AddComponent<Engine::FiniteStateMachine>(L"FSM", (int)DefaultEnemy::FSM::End);
	_pFSM->AddState((int)DefaultEnemy::FSM::Idle, DefaultEnemyIdle::Create(this));
	_pFSM->AddState((int)DefaultEnemy::FSM::Move, DefaultEnemyMove::Create(this));
	_pFSM->ChangeState((int)DefaultEnemy::FSM::Idle);
}

void DefaultEnemyScript::Update(const float& deltaTime)
{
	if (Input::IsKeyDown(DIK_M))
	{
		gameObject.SetDead();
	}
}

void DefaultEnemyScript::LateUpdate(const float& deltaTime)
{
}


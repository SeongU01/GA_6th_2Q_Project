#include "DefaultEnemyScript.h"
#include "Map.h"
#include "Grid.h"
#include "Tile.h"
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
#include "Defense.h"
#include "DefenseScript.h"
#include "TextRenderer.h"
#include "ToolTip.h"

#include "Attribute.h"
#include "AttackCollider.h"
#include "HPHUD.h"
#include "AttributeHUD.h"
#include "HitColor.h"

//state
#include "DefaultEnemyIdle.h"
#include "DefaultEnemyMove.h"
#include "DefaultEnemyWeakAttack.h"
#include "DefaultEnemyStrongAttack.h"
#include "DefaultEnemyDeath.h"

#include "DefaultEnemyInfomation.h"
#include "DataManager.h"
#include "Client_Define.h"

DefaultEnemyScript::DefaultEnemyScript(const wchar_t* name, const Vector3& startPos, const std::wstring& _targetName)
	:MonoBehavior(name),_startPosition(startPos),_targetObjectName(_targetName)
{
	
}

void DefaultEnemyScript::Awake()
{
	Engine::Collider* pCollider = AddComponent<Engine::Collider>(L"Body");
	pCollider->SetScale(Vector3(90.f, 90.f, 0.f));

#ifdef _DEBUG
	_pOwner->_isDrawCollider = true;
#endif // _DEBUG


	//TODO: FSM 작성하기
	_pHP=AddComponent<HP>(L"HP", 3);
	AddComponent<HPHUD>(_pHP, 1);

	_aStar = AddComponent<AStar>(L"AStar",_targetObjectName);
	_movement = AddComponent<GridMovement>(L"Movement",500.f);
	_pAnimation = AddComponent<Engine::Animation>(L"Animation");
	if (false == _pAnimation->LoadAnimation(L"Enemy_Default_DefaultEnemy"))
		throw std::runtime_error("can't load animation!");
	_pAnimation->ChangeAnimation(L"Idle");
	Engine::SpriteRenderer* pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();
	pSpriteRenderer->BindAnimation(_pAnimation);

	Pannel::PannelInfo info;
	info.parent = &transform;
	info.position = Vector3(0.f, -170.f, 0.f);
	info.size = Vector3{ 200, 50, 0 }; //크기
	info.fillColor = 0x99AEAEAE; //색상
	info.outlineColor = 0xFF000000; //테두리 색상
	info.opacity = 0.4f;
	_pPannel = Pannel::Create(info);
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Ememyinfo", _pPannel);
	_pPannel->AddComponent<Engine::TextRenderer>(L"TextRenderer",D2D1::ColorF::Black,20.f);
	_pPannel->SetActive(false);
	_pToolTip = AddComponent<ToolTip>(L"DefaultToolTip");
	_pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Character_001"), Vector3(0.0f, 0.0f, 0.0f));
	// 임시 추가한것
	_pAttribute = AddComponent<Attribute>();
	_pAttackCollider = AddComponent<AttackCollider>();
	AddComponent<AttributeHUD>(_pAttribute);
	AddComponent<HitColor>();
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

	Grid* pGrid=Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map")->GetComponent<Grid>();
	
	pGrid->GetTiles()[_gridPosition.y][_gridPosition.x]->canMove = false;

	_pFSM = AddComponent<Engine::FiniteStateMachine>(L"FSM", (int)DefaultEnemy::FSM::End);
	_pFSM->AddState((int)DefaultEnemy::FSM::Idle, DefaultEnemyIdle::Create(this));
	_pFSM->AddState((int)DefaultEnemy::FSM::Move, DefaultEnemyMove::Create(this));
	_pFSM->AddState((int)DefaultEnemy::FSM::WeakAttack, DefaultEnemyWeakAttack::Create(this));
	_pFSM->AddState((int)DefaultEnemy::FSM::StrongAttack, DefaultEnemyStrongAttack::Create(this));
	_pFSM->AddState((int)DefaultEnemy::FSM::Death, DefaultEnemyDeath::Create(this));
	_pFSM->ChangeState((int)DefaultEnemy::FSM::Idle);
}

void DefaultEnemyScript::Update(const float& deltaTime)
{
	
}

void DefaultEnemyScript::LateUpdate(const float& deltaTime)
{
	if (_pHP->IsZeroHP())
	{
		_pFSM->ChangeState((int)DefaultEnemy::FSM::Death);
	}
}

void DefaultEnemyScript::OnCollisionEnter(Engine::CollisionInfo& info)
{
	
}

void DefaultEnemyScript::OnCollision(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();
	if (*pOther == L"Mouse")
	{
		DefaultEnemyState* currState = static_cast<DefaultEnemyState*>(_pFSM->GetCurrState(_pFSM->GetCurrState()));
		currState->ShowInfo();
	}
	
}

void DefaultEnemyScript::OnCollisionExit(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();
	if (*pOther == L"Mouse")
	{
		DefaultEnemyState* currState = static_cast<DefaultEnemyState*>(_pFSM->GetCurrState(_pFSM->GetCurrState()));
		currState->CloseInfo();
	}
}


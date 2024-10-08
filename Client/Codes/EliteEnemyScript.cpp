#include "EliteEnemyScript.h"
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
#include "ToolTip.h"
#include "Defense.h"
#include "DefenseScript.h"
#include "Zero.h"
#include "Player.h"
#include "TextRenderer.h"

#include "Attribute.h"
#include "AttributeHUD.h"
#include "AttackCollider.h"
#include "HitColor.h"

//state
#include "EliteEnemyIdle.h"
#include "EliteEnemyMove.h"
#include "EliteEnemyNomalAttack.h"
#include "EliteEnemySuperSlash.h"
#include "EliteEnemyWeekSearch.h"
#include "EliteEnemyGetShield.h"
#include "EliteEnemyDeath.h"


#include "EliteEnemyInfomation.h"
#include "Client_Define.h"

EliteEnemyScript::EliteEnemyScript(const wchar_t* name, const Vector3& startPos, const std::wstring& _targetName)
	:MonoBehavior(name),_startPosition(startPos),_targetObjectName(_targetName)
{
}

void EliteEnemyScript::Awake()
{
	Engine::Collider* pCollider = AddComponent<Engine::Collider>(L"Body");
	pCollider->SetScale(Vector3(90.f, 90.f, 0.f));

	//_pOwner->_isDrawCollider = true;

	//TODO: FSM 작성하기
	_pHP = AddComponent<HP>(L"HP", 5);
	AddComponent<HPHUD>(_pHP, 1);
	_aStar = AddComponent<AStar>(L"AStar", _targetObjectName);
	_movement = AddComponent<GridMovement>(L"Movement", 500.f);
	_pAnimation = AddComponent<Engine::Animation>(L"Animation");
	if (false == _pAnimation->LoadAnimation(L"Enemy_Elite_EliteEnemy"))
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
	_pPannel->AddComponent<Engine::TextRenderer>(L"TextRenderer", D2D1::ColorF::Black, 20.f,DWRITE_FONT_WEIGHT_BOLD);
	_pPannel->SetActive(false);

	_pToolTip =AddComponent<ToolTip>(L"EliteToolTip");
	_pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Character_003"), Vector3(0.0f, 0.0f, 0.0f));

	// 임시 추가한것
	_pAttribute = AddComponent<Attribute>();
	_pAttackCollider = AddComponent<AttackCollider>();
	AddComponent<AttributeHUD>(_pAttribute);
	AddComponent<HitColor>();

}

void EliteEnemyScript::Start()
{
	_pTargetObject = Engine::FindObject((int)LayerGroup::Object, L"Defense", _targetObjectName.c_str());
	_pDefense = _pTargetObject->GetComponent<DefenseScript>(L"DefenseScript");
	_pPlayer = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->GetComponent<Player>();
	_gridPosition = _startPosition;
	_targetPosition = _pDefense->GetGridPosition();
	_aStar->SetGridMovement(_movement);
	_aStar->SetGoalPosition(_pDefense->GetGridPosition());
	_aStar->SetGridPosition(_startPosition);
	transform.position = _movement->_grid->GetTileCenter((int)_gridPosition.x, (int)_gridPosition.y);

	Grid* pGrid=Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map")->GetComponent<Grid>();
	pGrid->GetTiles()[(int)_gridPosition.y][(int)_gridPosition.x]->canMove = false;


	_pFSM = AddComponent<Engine::FiniteStateMachine>(L"FSM", (int)EliteEnemy::FSM::End);
	_pFSM->AddState((int)EliteEnemy::FSM::Idle, EliteEnemyIdle::Create(this));
	_pFSM->AddState((int)EliteEnemy::FSM::Move, EliteEnemyMove::Create(this));
	_pFSM->AddState((int)EliteEnemy::FSM::NomalAttack, EliteEnemyNomalAttack::Create(this));
	_pFSM->AddState((int)EliteEnemy::FSM::SuperSlash, EliteEnemySuperSlash::Create(this));
	_pFSM->AddState((int)EliteEnemy::FSM::WeekSearch, EliteEnemyWeekSearch::Create(this));
	_pFSM->AddState((int)EliteEnemy::FSM::GetShield, EliteEnemyGetShield::Create(this));
	_pFSM->AddState((int)EliteEnemy::FSM::Death, EliteEnemyDeath::Create(this));
	_pFSM->ChangeState((int)EliteEnemy::FSM::Idle);
}

void EliteEnemyScript::Update(const float& deltaTime)
{
	HP* pTarGetHp = _pDefense->GetComponent<HP>();
	if (pTarGetHp->hp <= 0)
	{
		ChangeTarget();
	}
}

void EliteEnemyScript::LateUpdate(const float& deltaTime)
{
	if (_pHP->IsZeroHP())
	{
		_pFSM->ChangeState((int)EliteEnemy::FSM::Death);
	}
}

void EliteEnemyScript::OnCollisionEnter(Engine::CollisionInfo& info)
{

}

void EliteEnemyScript::OnCollision(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();
	if (*pOther == L"Mouse")
	{
		EliteEnemyState* currState = static_cast<EliteEnemyState*>(_pFSM->GetCurrState(_pFSM->GetCurrState()));
		currState->ShowToolTip();
	}
}

void EliteEnemyScript::OnCollisionExit(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();
	if (*pOther == L"Mouse")
	{
		EliteEnemyState* currState = static_cast<EliteEnemyState*>(_pFSM->GetCurrState(_pFSM->GetCurrState()));
		currState->CloseToolTip();
	}
}

void EliteEnemyScript::ChangeTarget()
{
	std::list<Engine::GameObject*>* defenseList = Engine::FindObjectList((int)LayerGroup::Object, L"Defense");
	std::vector<std::pair<float, Engine::GameObject*>> defenses;
	if (nullptr != defenseList)
	{
		for (auto it = defenseList->begin(); it != defenseList->end(); ++it)
		{
			Engine::GameObject* obj = *it;
			HP* pHP = obj->GetComponent<HP>();
			if (pHP->hp <= 0)
			{
				continue;
			}
			else
			{
				Vector3 distanceVector = this->transform.position - obj->transform.position;
				float distance = XMVector2Length({ distanceVector.x,distanceVector.y }).m128_f32[0];
				std::pair<float, Engine::GameObject*> temp = { distance,obj };
				defenses.push_back(temp);
			}
		}

		if (defenses.empty())
		{
			_targetPosition = _gridPosition;
		}
		else
		{

			std::sort(defenses.begin(), defenses.end(), [](const std::pair<float, Engine::GameObject*>& a, const std::pair<float, Engine::GameObject*>& b)
				{
					return a.first < b.first;
				}
			);
			
			_pNextTargetObject = defenses[0].second;
			_targetObjectName = _pNextTargetObject->GetName();
			_pDefense = _pNextTargetObject->GetComponent<DefenseScript>();
			
		}
	
	}
	else
	{
		throw	std::runtime_error("No objects found for the specified tag.");
	}
}

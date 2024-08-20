#include "BossEnemyScript.h"
#include "Grid.h"
#include "Tile.h"
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

//state
#include "BossEnemyIdle.h"
#include "BossEnemyMove.h"

#include "BossEnemyInformation.h"
#include "Client_Define.h"

BossEnemyScript::BossEnemyScript(const wchar_t* name, const Vector3& startPos, const std::wstring& _targetName)
	:MonoBehavior(name),_startPosition(startPos), _targetObjectName(_targetName)
{
}

void BossEnemyScript::Awake()
{
	Engine::Collider* pCollider = AddComponent<Engine::Collider>(L"Body");
	pCollider->SetScale(Vector3(90.f, 90.f, 0.f));

	//_pOwner->_isDrawCollider = true;

	_pHP = AddComponent<HP>(L"HP", 20);
	AddComponent<HPHUD>(_pHP, 1);

	_aStar = AddComponent<AStar>(L"AStar", _targetObjectName);
	_movement = AddComponent<GridMovement>(L"Movement", 500.f);

	_pAnimation = AddComponent<Engine::Animation>(L"Animation");
	if (false == _pAnimation->LoadAnimation(L"Enemy_Boss_BossEnemy"))
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
	_pPannel->AddComponent<Engine::TextRenderer>(L"TextRenderer", D2D1::ColorF::Black, 20.f, DWRITE_FONT_WEIGHT_BOLD);
	_pPannel->SetActive(false);

	_pToolTip = AddComponent<ToolTip>(L"EliteToolTip");
	_pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Character_003"), Vector3(0.0f, 0.0f, 0.0f));

	// 임시 추가한것
	_pAttribute = AddComponent<Attribute>();
	_pAttackCollider = AddComponent<AttackCollider>();
	AddComponent<AttributeHUD>(_pAttribute);
}

void BossEnemyScript::Start()
{
	_pPlayer = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->GetComponent<Player>();
	_gridPosition = _startPosition;
	_aStar->SetGridMovement(_movement);
	_aStar->SetGridPosition(_startPosition);
	transform.position = _movement->_grid->GetTileCenter((int)_gridPosition.x, (int)_gridPosition.y);

	Grid* pGrid = Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map")->GetComponent<Grid>();
	pGrid->GetTiles()[(int)_gridPosition.y][(int)_gridPosition.x]->canMove = false;

	_pFSM = AddComponent<Engine::FiniteStateMachine>(L"FSM", (int)BossEnemy::FSM::End);
	_pFSM->AddState((int)BossEnemy::FSM::Idle, BossEnemyIdle::Create(this));
	_pFSM->AddState((int)BossEnemy::FSM::Move, BossEnemyMove::Create(this));
	_pFSM->ChangeState((int)BossEnemy::FSM::Idle);
}

void BossEnemyScript::Update(const float& deltaTime)
{
	_targetPosition = _pPlayer->GetGridPosition();
}

void BossEnemyScript::LateUpdate(const float& deltaTime)
{
}

void BossEnemyScript::OnCollisionEnter(Engine::CollisionInfo& info)
{
}

void BossEnemyScript::OnCollision(Engine::CollisionInfo& info)
{
}

void BossEnemyScript::OnCollisionExit(Engine::CollisionInfo& info)
{
}

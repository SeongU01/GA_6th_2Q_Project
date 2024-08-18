#include "DefenseScript.h"
#include "Grid.h"
#include "GridInfo.h"
#include "Tile.h"
#include "HP.h"
#include "ToolTip.h"
#include "SpriteRenderer.h"
#include "Collider.h"
#include "Client_Define.h"

DefenseScript::DefenseScript(const wchar_t* name, const std::pair<Vector3, Vector3>& gridRange, const wchar_t* type)
	:MonoBehavior(name), _name(type), _gridRange(gridRange)
{
	
}

void DefenseScript::Awake()
{
	Engine::Collider* pCollider = AddComponent<Engine::Collider>(L"Body");
	pCollider->SetOffset({ 0.0f,-60.0f,0.0f });
	if (_name == L"Defense_Generator") //발전기
		pCollider->SetScale(Vector3(100.f, 200.f, 0.f));
	else if (_name == L"Defense_Command")
		pCollider->SetScale(Vector3(190.f, 200.f, 0.f));

	_pGridInfo = AddComponent<GridInfo>(L"GridInfo");
	_pHP = GetComponent<HP>(L"HP");
	_pSpriteRenderer = GetComponent<Engine::SpriteRenderer>(L"SpriteRenderer");
	_pToolTip = AddComponent<ToolTip>(L"name");
	if(_name==L"Defense_Generator") //발전기
		_pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Structure_002"), Vector3(-200.0f, -100.0f, 0.0f));
	else if(_name ==L"Defense_Command")
		_pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Structure_003"), Vector3(-200.0f, -100.0f, 0.0f));
}

void DefenseScript::Start()
{
	_pOwner->_isDrawCollider = true;
	float x = (_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.first.x, (int)_gridRange.first.y).x +
		_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.second.x, (int)_gridRange.second.y).x) / 2;
	float y = (_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.first.x, (int)_gridRange.first.y).y +
		_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.second.x, (int)_gridRange.second.y).y) / 2;

	transform.position = Vector3(x, y, 0.f);
	for (int y = (int)_gridRange.first.y; y < (int)_gridRange.second.y + 1; y++)
	{
		for (int x = (int)_gridRange.first.x; x < (int)_gridRange.second.x + 1; x++)
		{
			_pGridInfo->GetGrid()->GetTiles()[y][x]->canMove = false;
		}
	}
	_gridPosition = { _gridRange.second.x, _gridRange.second.y ,0.f };
}

void DefenseScript::Update(const float& deltaTime)
{
}

void DefenseScript::LateUpdate(const float& deltaTime)
{
	_pSpriteRenderer->SetIndex((_pHP->GetMaxHP() - _pHP->hp));
}

void DefenseScript::OnCollisionEnter(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();
	if (*pOther == L"Mouse")
	{
		_pToolTip->ActiveToolTip(true);
	}
}

void DefenseScript::OnCollision(Engine::CollisionInfo& info)
{
}

void DefenseScript::OnCollisionExit(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();
	if (*pOther == L"Mouse")
	{
		_pToolTip->ActiveToolTip(false);
	}
}






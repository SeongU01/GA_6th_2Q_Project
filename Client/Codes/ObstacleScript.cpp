#include "ObstacleScript.h"
#include "GridInfo.h"
#include "Grid.h"
#include "Collider.h"
#include "ToolTip.h"
#include "Tile.h"

ObstacleScript::ObstacleScript(const wchar_t* name, const std::pair<Vector3, Vector3>& gridRange, const wchar_t* texture )
	:MonoBehavior(name), _type(texture), _gridRange(gridRange)
{
}

void ObstacleScript::Awake()
{

	_pGridInfo = AddComponent<GridInfo>(L"GridInfo");
	
	Engine::Collider* pCollider = AddComponent<Engine::Collider>(L"Body");
	pCollider->SetOffset({ 0.0f,-30.0f,0.0f });
	_pToolTip = AddComponent<ToolTip>(L"name");
	if (_type == L"Obstacle_BrokenBuilding")
	{
		pCollider->SetScale(Vector3(100.f, 160.f, 0.f));
		_pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Structure_001"), Vector3(-200.0f, -100.0f, 0.0f));
	}
	else if (_type == L"Obstacle_Portal")
	{ 
		pCollider->SetScale(Vector3(100.f, 140.f, 0.f));
		_pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Structure_004"), Vector3(-200.0f, -100.0f, 0.0f));
	}
	else if (_type == L"Obstacle_Mountain")
	{
		pCollider->SetScale(Vector3(200.f, 150.f, 0.f));
		_pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Structure_000"), Vector3(-200.0f, -100.0f, 0.0f));
	}

}

void ObstacleScript::Start()
{

	float x = (_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.first.x, (int)_gridRange.first.y).x +
		_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.second.x, (int)_gridRange.second.y).x) / 2;
	float y = (_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.first.x, (int)_gridRange.first.y).y +
		_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.second.x, (int)_gridRange.second.y).y) / 2;

	transform.position=Vector3(x,y,0.f);
	for (int y = (int)_gridRange.first.y; y < (int)_gridRange.second.y + 1; y++)
	{
		for (int x = (int)_gridRange.first.x; x < (int)_gridRange.second.x + 1; x++)
		{
			_pGridInfo->GetGrid()->GetTiles()[y][x]->canMove = false;
		}
	}
}

void ObstacleScript::Update(const float& deltaTime)
{
}

void ObstacleScript::LateUpdate(const float& deltaTime)
{
}

void ObstacleScript::OnCollisionEnter(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();
	if (*pOther == L"Mouse")
	{
		_pToolTip->ActiveToolTip(true);
	}
}

void ObstacleScript::OnCollision(Engine::CollisionInfo& info)
{
}

void ObstacleScript::OnCollisionExit(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();
	if (*pOther == L"Mouse")
	{
		_pToolTip->ActiveToolTip(false);
	}
}
